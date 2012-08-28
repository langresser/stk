//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2004 SuperTuxKart-Team
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

#ifndef HEADER_LINEAR_WORLD_HPP
#define HEADER_LINEAR_WORLD_HPP

#include <vector>

#include "modes/world_with_rank.hpp"
#include "tracks/track_sector.hpp"
#include "utils/aligned_array.hpp"

class SFXBase;

/*
 * A 'linear world' is a subcategory of world used in 'standard' races, i.e.
 * with a start line and a road that loops. This includes management of drivelines
 * and lap counting.
 * \ingroup modes
 */
class LinearWorld : public WorldWithRank
{
private:
    /** Sfx for the final lap. */
    SFXBase     *m_last_lap_sfx;

    /** Last lap sfx should only be played once. */
    bool         m_last_lap_sfx_played;
    
    bool         m_last_lap_sfx_playing;

    /** The fastest lap time. */
    float       m_fastest_lap;

    // ------------------------------------------------------------------------
    /** Some additional info that needs to be kept for each kart
     * in this kind of race.
     */
    class KartInfo
    {
    public:
        /** Number of finished(!) laps. */
        int         m_race_lap;

        /** Time at finishing last lap. */
        float       m_time_at_last_lap;

        /** Time at start of a new lap. */
        float       m_lap_start_time;

        /** During last lap only: estimated finishing time!   */
        float       m_estimated_finish;

        /** Stores the current graph node and track coordinates etc. */
        TrackSector m_current_sector;

        /** Initialises all fields. */
        KartInfo()  { reset(); }
        // --------------------------------------------------------------------
        /** Re-initialises all data. */
        void reset()
        {
            m_race_lap         = -1;
            m_lap_start_time   = 0;
            m_time_at_last_lap = 99999.9f;
            m_estimated_finish = -1.0f;
            m_current_sector.reset();
        }
        // --------------------------------------------------------------------
        /** Returns a pointer to the current node object. */
        TrackSector *getSector() {return &m_current_sector; }
        // --------------------------------------------------------------------
        /** Returns a pointer to the current node object. */
        const TrackSector *getSector() const {return &m_current_sector; }
    };
    // ------------------------------------------------------------------------

protected:
    RaceGUIBase::KartIconDisplayInfo* m_kart_display_info;

    /** This vector contains an 'KartInfo' struct for every kart in the race.
      * This member is not strictly private but try not to use it directly outside
      * tightly related classes (e.g. AI)
      */
    AlignedArray<KartInfo> m_kart_info;

    
    /** Linear races can trigger rescues for one additional reason : shortcuts.
      * It may need to do some specific world before calling the generic Kart::forceRescue
      */
    void          rescueKartAfterShortcut(AbstractKart* kart, KartInfo& kart_info);
    virtual void  checkForWrongDirection(unsigned int i);
    void          updateRacePosition();
    virtual float estimateFinishTimeForKart(AbstractKart* kart) OVERRIDE;

public:
                  LinearWorld();
   /** call just after instanciating. can't be moved to the contructor as child
       classes must be instanciated, otherwise polymorphism will fail and the
       results will be incorrect */
    virtual void  init() OVERRIDE;
    virtual      ~LinearWorld();

    virtual void  update(float delta) OVERRIDE;
    int           getSectorForKart(const AbstractKart *kart) const;
    float         getDistanceDownTrackForKart(const int kart_id) const;
    float         getDistanceToCenterForKart(const int kart_id) const;
    float         getEstimatedFinishTime(const int kart_id) const;
    int           getLapForKart(const int kart_id) const;
    float         getTimeAtLapForKart(const int kart_id) const;

    virtual  RaceGUIBase::KartIconDisplayInfo* 
                  getKartsDisplayInfo() OVERRIDE;
    virtual void  moveKartAfterRescue(AbstractKart* kart) OVERRIDE;
    virtual void  restartRace() OVERRIDE;
    virtual void  newLap(unsigned int kart_index) OVERRIDE;
    
    // ------------------------------------------------------------------------    
    /** Returns if this race mode has laps. */
    virtual bool  raceHasLaps() OVERRIDE { return true; }
    // ------------------------------------------------------------------------    
    /** Returns if this race mode has bonus items. */
    virtual bool  haveBonusBoxes() OVERRIDE { return true; }
    // ------------------------------------------------------------------------    
    /** Override settings from base class */
    virtual bool useChecklineRequirements() const OVERRIDE { return true; }
    // ------------------------------------------------------------------------    
    /** Returns true if the kart is on a valid driveline quad.
     *  \param kart_index  Index of the kart. */
    bool          isOnRoad(unsigned int kart_index) const 
                  { return m_kart_info[kart_index].getSector()->isOnRoad(); }
    
    // ------------------------------------------------------------------------
    int           getKartLap(unsigned int kart_index) const
                  {
                      if (kart_index < m_kart_info.size())
                          return m_kart_info[kart_index].m_race_lap;
                      else
                          return -1;
                  }
    
    TrackSector& getTrackSector(unsigned int kart_index)
                  {
                      return m_kart_info[kart_index].m_current_sector;
                  }
    
};   // LinearWorld

#endif
