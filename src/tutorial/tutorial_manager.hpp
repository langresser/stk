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

#ifndef TUTORIALMANAGER_H
#define TUTORIALMANAGER_H

#include <map>

#include "tutorial/tutorial.hpp"
#include "tutorial/tutorial_data.hpp"

#include "utils/no_copy.hpp"

#include <fstream>

class XMLNode;

/**
  * \brief main class to handle the tutorials list
  * \ingroup tutorial
  */
class TutorialManager : public NoCopy
{

private:
    
    typedef std::map<std::string, Tutorial*> TutorialsList;
    TutorialsList m_tutorials_list;

    void       load              ();

public:
               TutorialManager     ();
              ~TutorialManager     ();
    void       addTutorial      (Tutorial * m_tutorial);
    void       addTutorial      (const std::string& filename);

    vector <const Tutorial*> getTutorialsList();
    
    const Tutorial *getTutorial     (const std::string& id);

    void       raceFinished      ();        
    
};   // TutorialManager

extern TutorialManager * m_tutorial_manager;
#endif // TUTORIALMANAGER_H
