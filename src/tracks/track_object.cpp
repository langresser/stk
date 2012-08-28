//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2009 Joerg Henrichs
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "tracks/track_object.hpp"

#include "audio/sfx_base.hpp"
#include "audio/sfx_buffer.hpp"
#include "audio/sfx_manager.hpp"
#include "graphics/irr_driver.hpp"
#include "graphics/lod_node.hpp"
#include "graphics/particle_emitter.hpp"
#include "graphics/particle_kind_manager.hpp"
#include "io/file_manager.hpp"
#include "io/xml_node.hpp"
#include "items/item_manager.hpp"
#include "modes/overworld.hpp"
#include "modes/world.hpp"
#include "tracks/track.hpp"

#include <IMeshSceneNode.h>
#include <ISceneManager.h>
#include <IParticleSystemSceneNode.h>

/** A track object: any additional object on the track. This object implements
 *  a graphics-only representation, i.e. there is no physical representation.
 *  Derived classes can implement a physical representation (see 
 *  physics/physical_object) or animations.
 * \param xml_node The xml node from which the initial data is taken. This is
 *                 for now: initial position, initial rotation, name of the
 *                 model, enable/disable status, timer information.
 */
TrackObject::TrackObject(const XMLNode &xml_node)
{
    m_init_xyz   = core::vector3df(0,0,0);
    m_init_hpr   = core::vector3df(0,0,0);
    m_init_scale = core::vector3df(1,1,1);
    m_enabled    = true;
    m_is_looped  = false;
    m_sound      = NULL;
    m_mesh       = NULL;
    m_node       = NULL;
    m_emitter    = NULL;
    m_lod_emitter_node = NULL;
    
    xml_node.get("xyz",     &m_init_xyz  );
    xml_node.get("hpr",     &m_init_hpr  );
    xml_node.get("scale",   &m_init_scale);
    xml_node.get("enabled", &m_enabled   );
    xml_node.get("looped",  &m_is_looped );
    std::string model_name;
    xml_node.get("model",   &model_name  );
    std::string sound;
    xml_node.get("sound",   &sound       );

    m_interaction = "static";
    xml_node.get("interaction", &m_interaction);
    xml_node.get("lod_group", &m_lod_group);
    
    std::string type;
    xml_node.get("type",    &type );

    m_type = type;

    bool trigger_when_near = false;
    float trigger_distance = 1.0f;
    
    if (xml_node.getName() == "particle-emitter")
    {
        m_type = "particle-emitter";
        std::string path;
        irr::core::vector3df emitter_origin;
        xml_node.get("kind", &path);
        xml_node.getXYZ(&emitter_origin);

        int clip_distance = -1;
        xml_node.get("clip_distance", &clip_distance);

        xml_node.get("conditions", &m_trigger_condition);
        
        try
        {
            ParticleKind* kind = ParticleKindManager::get()->getParticles( path.c_str() );
            if (kind == NULL)
            {
                throw std::runtime_error(path + " could not be loaded");
            }
            ParticleEmitter* emitter = new ParticleEmitter( kind, emitter_origin );
            
            if (clip_distance > 0)
            {
                scene::ISceneManager* sm = irr_driver->getSceneManager();
                scene::ISceneNode* sroot = sm->getRootSceneNode();
                LODNode* lod = new LODNode("particles", sroot, sm);
                lod->add(clip_distance, (scene::ISceneNode*)emitter->getNode(), true);
                //m_all_emitters.push_back(emitter);
                m_node = lod;
                m_lod_emitter_node = lod;
                m_emitter = emitter;
            }
            else
            {
                m_node = emitter->getNode(); // FIXME: this leaks
                m_emitter = emitter;
            }
            
            if (m_trigger_condition.size() > 0)
            {
                m_emitter->setCreationRateAbsolute(0.0f);
            }
        }
        catch (std::runtime_error& e)
        {
            fprintf(stderr, "[Track] WARNING: Could not load particles '%s'; cause :\n    %s", path.c_str(), e.what());
        }
    }
    // FIXME: at this time sound emitters are just disabled in multiplayer
    //        otherwise the sounds would be constantly heard
    else if (sound.size() > 0 && race_manager->getNumLocalPlayers() < 2)
    {
        float rolloff = 0.5;
        xml_node.get("rolloff",  &rolloff );
        float volume = 1.0;
        xml_node.get("volume",   &volume );
        
        xml_node.get("play-when-near", &trigger_when_near);
        
        xml_node.get("distance", &trigger_distance);

        xml_node.get("conditions", &m_trigger_condition);
        
        float max_dist = 390.0f;
        xml_node.get("max_dist",      &max_dist );
        
        // first try track dir, then global dir
        std::string soundfile = file_manager->getModelFile(sound);
        if (!file_manager->fileExists(soundfile))
        {
            soundfile = file_manager->getSFXFile(sound);
        }
        
        SFXBuffer* buffer = new SFXBuffer(soundfile,
                                          true /* positional */,
                                          rolloff,
                                          max_dist,
                                          volume);
        buffer->load();
        
        m_sound = sfx_manager->createSoundSource(buffer);
        if (m_sound != NULL)
        {
            m_sound->position(m_init_xyz);
            if (!trigger_when_near && m_trigger_condition.empty())
            {
                m_sound->setLoop(true);
                m_sound->play();
            }
        }
        else
        {
            fprintf(stderr, 
                 "[TrackObject] Sound emitter object could not be created\n");
        }
    }
    else if (type == "action-trigger")
    {
        trigger_when_near = true;
        
        xml_node.get("distance", &trigger_distance);
        
        xml_node.get("action", &m_action);

        if (m_action.size() == 0)
        {
            fprintf(stderr, "[TrackObject] WARNING: action-trigger has no action defined\n");
        }
    }
    
    // Some animated objects (billboards, sound emitters, action triggers)
    // don't use this scene node
    if (model_name == "")
    {
        m_mesh = NULL;
        
        if (trigger_when_near)
        {
            ItemManager::get()->newItem(m_init_xyz, trigger_distance, this);
        }
    }
    else
    {
        std::string full_path = 
            World::getWorld()->getTrack()->getTrackFile(model_name);
        
        bool animated = (UserConfigParams::m_graphical_effects ||
                         World::getWorld()->getIdent() == IDENT_CUSTSCENE);
        
        if (file_manager->fileExists(full_path))
        {
            if (animated)
            {
                m_mesh = irr_driver->getAnimatedMesh(full_path);
            }
            else
            {
                m_mesh = irr_driver->getMesh(full_path);
            }
        }
        
        if(!m_mesh)
        {
            // If the model isn't found in the track directory, look 
            // in STK's model directory.
            full_path = file_manager->getModelFile(model_name);
            m_mesh    = irr_driver->getAnimatedMesh(full_path);
            
            if(!m_mesh)
            {
                throw std::runtime_error("Model '" + model_name + "' cannot be found");
            }
        }

        m_mesh->grab();
        irr_driver->grabAllTextures(m_mesh);
        
        if (animated)
        {
            scene::IAnimatedMeshSceneNode *node =
                irr_driver->addAnimatedMesh((scene::IAnimatedMesh*)m_mesh);
            m_node = node;
            
            m_frame_start = node->getStartFrame();
            xml_node.get("frame-start", &m_frame_start);

            m_frame_end = node->getEndFrame();
            xml_node.get("frame-end", &m_frame_end);
        }
        else
        {
            m_node = irr_driver->addMesh(m_mesh);
            m_frame_start = 0;
            m_frame_end = 0;
        }
#ifdef DEBUG
        std::string debug_name = model_name+" (track-object)";
        m_node->setName(debug_name.c_str());
#endif

        if(!m_enabled)
            m_node->setVisible(false);

        m_node->setPosition(m_init_xyz);
        m_node->setRotation(m_init_hpr);
        m_node->setScale(m_init_scale);
    }
    reset();
}   // TrackObject

// ----------------------------------------------------------------------------

TrackObject::TrackObject(const core::vector3df& pos, const core::vector3df& hpr,
                         const core::vector3df& scale, const std::string& model_name)
{
    m_init_xyz   = pos;
    m_init_hpr   = hpr;
    m_init_scale = scale;
    m_enabled    = true;
    m_is_looped  = false;
    m_sound      = NULL;
    m_emitter    = NULL;
    
    // Some animated objects (billboards, sound emitters) don't use this scene node
    if (model_name == "")
    {
        m_node = NULL;
        m_mesh = NULL;
    }
    else
    {
        bool animated = (UserConfigParams::m_graphical_effects ||
                         World::getWorld()->getIdent() == IDENT_CUSTSCENE);
                         
        if (file_manager->fileExists(model_name))
        {
            if (animated)
            {
                m_mesh = irr_driver->getAnimatedMesh(model_name);
            }
            else
            {
                m_mesh = irr_driver->getMesh(model_name);
            }
        }
        
        if(!m_mesh)
        {
            fprintf(stderr, "Warning: '%s' not found and is ignored.\n",
                    model_name.c_str());
            return;
        }
        
        m_mesh->grab();
        irr_driver->grabAllTextures(m_mesh);
        
        if (animated)
        {
            scene::IAnimatedMeshSceneNode *node = irr_driver->addAnimatedMesh((scene::IAnimatedMesh*)m_mesh);
            m_node = node;
            
            m_frame_start = node->getStartFrame();
            m_frame_end = node->getEndFrame();
        }
        else
        {
            m_node = irr_driver->addMesh(m_mesh);
            m_frame_start = 0;
            m_frame_end = 0;
        }
        
#ifdef DEBUG
        std::string debug_name = model_name+" (track-object)";
        m_node->setName(debug_name.c_str());
#endif
        
        if(!m_enabled)
            m_node->setVisible(false);
        
        m_node->setPosition(m_init_xyz);
        m_node->setRotation(m_init_hpr);
        m_node->setScale(m_init_scale);
    }
    reset();
}   // TrackObject

// ----------------------------------------------------------------------------
TrackObject::TrackObject()
{
    m_node  = NULL;
    m_mesh  = NULL;    
    m_sound =  NULL;
    m_emitter = NULL;
}   // TrackObject()

// ----------------------------------------------------------------------------
/** Destructor. Removes the node from the scene graph, and also
 *  drops the textures of the mesh. Sound buffers are also freed.
 */
TrackObject::~TrackObject()
{
    if (m_emitter)
    {
        if (m_lod_emitter_node != NULL)
        {
            irr_driver->removeNode(m_lod_emitter_node);
            m_emitter->unsetNode();
        }
        delete m_emitter; // this will also delete m_node
    }
    else if (m_node)
        irr_driver->removeNode(m_node);
    
    if(m_mesh)
    {
        irr_driver->dropAllTextures(m_mesh);
        m_mesh->drop();
        if(m_mesh->getReferenceCount()==1)
            irr_driver->removeMeshFromCache(m_mesh);
    }
    
    if (m_sound)
    {
        delete m_sound->getBuffer();
        sfx_manager->deleteSFX(m_sound);
    }
}   // ~TrackObject

// ----------------------------------------------------------------------------
/** Initialises an object before a race starts.
 */
void TrackObject::reset()
{
    if(!m_node) return;
    if(m_node->getType()==scene::ESNT_ANIMATED_MESH)
    {
        scene::IAnimatedMeshSceneNode *a_node =
            (scene::IAnimatedMeshSceneNode*)m_node;

        a_node->setPosition(m_init_xyz);
        a_node->setRotation(m_init_hpr);
        a_node->setScale(m_init_scale);
        a_node->setLoopMode(m_is_looped);

        if(m_is_looped)
        {
            a_node->setFrameLoop(m_frame_start, m_frame_end);
        }
    }
}   // reset
// ----------------------------------------------------------------------------
/** Enables or disables this object. This affects the visibility, i.e. 
 *  disabled objects will not be displayed anymore.
 *  \param mode Enable (true) or disable (false) this object.
 */
void TrackObject::setEnable(bool mode)
{
    m_enabled = mode;
    if(m_node)
        m_node->setVisible(m_enabled);
}   // setEnable
// ----------------------------------------------------------------------------
/** This function is called from irrlicht when a (non-looped) animation ends.
 */
void TrackObject::OnAnimationEnd(scene::IAnimatedMeshSceneNode* node)
{
}   // OnAnimationEnd

// ----------------------------------------------------------------------------
void TrackObject::update(float dt)
{
    if (m_sound != NULL)
    {
        // muting when too far is implemented manually since not supported by OpenAL
        // so need to call this every frame to update the muting state if listener
        // moved
        m_sound->position(m_init_xyz);
    }
    
    if (m_emitter != NULL)
    {
        m_emitter->update(dt);
    }
}   // update
// ----------------------------------------------------------------------------

/** Implement callback from TriggerItemListener. Not used by all track objects. */
void TrackObject::onTriggerItemApproached(Item* who)
{
    if (m_sound != NULL && m_sound->getStatus() != SFXManager::SFX_PLAYING)
    {
        m_sound->play();
    }
    else if (m_action.size() > 0)
    {
        if (m_action == "garage")
        {
            dynamic_cast<OverWorld*>(World::getWorld())->scheduleReturnToGarage();
        }
        else
        {
            fprintf(stderr, "[TrackObject] WARNING: unknown action <%s>\n",
                    m_action.c_str());
        }
    }
}

// ----------------------------------------------------------------------------

/** if this is a sound object, play the object */
void TrackObject::triggerSound(bool loop)
{
    if (m_sound != NULL)
    {
        m_sound->setLoop(loop);
        m_sound->play();
    }
}

// ----------------------------------------------------------------------------

/** if this is a sound object, stop the object */
void TrackObject::stopSound()
{
    if (m_sound != NULL) m_sound->stop();
}

// ----------------------------------------------------------------------------

void TrackObject::triggerParticles()
{
    if (m_emitter != NULL)
    {
        m_emitter->setCreationRateAbsolute(1.0f);
        m_emitter->setParticleType(m_emitter->getParticlesInfo());
    }
}

// ----------------------------------------------------------------------------

