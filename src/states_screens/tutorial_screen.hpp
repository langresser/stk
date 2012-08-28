//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2010 Alejandro Santiago
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

#ifndef TUTORIALSCREEN_H
#define TUTORIALSCREEN_H

#include <irrString.h>
#include "guiengine/screen.hpp"
#include "guiengine/CGUISpriteBank.h"

using namespace irr::core;

const std::string BASIC_DRIVING = "basicdriving";
const std::string SHARP_TURN = "st";
const std::string NITRO = "nt";
const std::string COLLECTIBLE_WEAPONS = "cw";
const std::string SHOOTING_BACKWARDS = "sb";

class TutorialScreen : public GUIEngine::Screen, public GUIEngine::ScreenSingleton<TutorialScreen>
{
    
    friend class GUIEngine::ScreenSingleton<TutorialScreen>;
    TutorialScreen();

    irr::gui::STKModifiedSpriteBank* m_icon_bank;


    public:
    /** \brief implement callback from parent class GUIEngine::Screen */
    virtual void loadedFromFile();

    /** \brief implement optional callback from parent class GUIEngine::Screen */
    void onUpdate(float dt, irr::video::IVideoDriver*);

    /** \brief implement callback from parent class GUIEngine::Screen */
    void init();

    /** \brief implement callback from parent class GUIEngine::Screen */
    void eventCallback(GUIEngine::Widget* widget, const std::string& name, const int playerID);
};

#endif // TUTORIALSCREEN_H
