#include "observer.h"
#include "subject.h"
#include "block.h"
#include "board.h"
#include "textdisplay.h"
#include "Property/property.h"
#include "Property/academic.h"
#include "Property/nonacademic.h"

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {

	// create the 40 blocks
	vector<Block> blocks;
	/*
	NonAcademic gooseNest{"Goose Nesting", 0, 0, Type::Gym}; // fix
	Academic ev1{"EV1", "Env", 220, 0, {18,90,250,700,875,1050}, 150};
	NonAcademic needlesHall{"NEEDLES HALL", 0, 0, Type::Gym}; // fix
	Academic ev2{"EV2", "Env", 220, 0, {18,90,250,700,875,1050}, 150};
	Academic ev3{"EV3", "Env", 240, 0, {20,100,300,750,925,1100}, 150};
	NonAcademic v1{"V1", 200, 1, Type::Residence};
	Academic phys{"PHYS", "Sci1", 260, 0, {22,110,330,800,975,1150}, 150};
	Academic b1{"B1", "Sci1", 260, 0, {22,110,330,800,975,1150}, 150};
	NonAcademic cif{"CIF", 150, 1, Type::Gym};
	Academic b2{"B2", "Sci1", 280, 0, {24,120,360,850,1025,1200}, 150};
	NonAcademic goToTims{"GO TO TIMS", 0, 0, Type::Gym}; // fix
	Academic eit{"EIT", "Sci2", 300, 0, {26,130,390,900,1100,1275}, 200};
	Academic esc{"ESC", "Sci2", 300, 0, {26,130,390,900,1100,1275}, 200};
	NonAcademic slc{"SLC", 0, 0, Type::Gym}; // fix
	Academic c2{"C2", "Sci2", 320, 0, {28,150,450,100,1200,1400}, 200};
	NonAcademic rev{"REV", 200, 1, Type::Residence};
	// needles hall next
	Academic mc{"MC", "Math", 350, 0, {35,175,500,1100,1300,1500}, 200};
	NonAcademic coopFee{"COOP FEE", 0, 0, Type::Gym}; // fix
	Academic dc{"DC", "Math", 400, 0, {50,200,600,1400,1700,2000}, 200};
	NonAcademic collectOSAP{"COLLECT OSAP", 0, 0, Type::Gym}; // fix
	Academic al{"AL", "Arts1", 40, 0, {2,10,30,90,160,250}, 50};
	// slc next
	Academic ml{"ML", "Arts1", 60, 0, {4,20,60,180,320,450}, 50};
	NonAcademic tuition{"TUITION", 0, 0, Type::Gym}; // fix
	NonAcademic mkv{"MKV", 200, 1, Type::Residence};
	Academic ech{"ECH", "Arts2", 100, 0, {6,30,90,270,400,550}, 50};
	// needles hall next
	Academic pas{"PAS", "Arts2", 100, 0, {6,30,90,270,400,550}, 50};
	Academic hh{"HH", "Arts2", 120, 0, {8,40,100,300,450,600}, 50};
	NonAcademic timsLine{"DC Tims Line", 0, 0, Type::Gym}; // fix
	Academic rch{"RCH", "Eng", 140, 0, {10,50,150,450,625,750}, 100};
	NonAcademic pac{"PAC", 150, 1, Type::Gym};
	Academic dwe{"DWE", "Eng", 140, 0, {10,50,150,450,625,750}, 100};
	Academic cph{"CPH", "Eng", 160, 0, {12,60,180,500,700,900}, 100};
	NonAcademic uwp{"UWP", 200, 1, Type::Residence};
	Academic lhi{"LHI", "Health", 180, 0, {14,70,200,550,750,950}, 100};
	// slc next
	Academic bmh{"BMH", "Health", 180, 0, {14,70,200,550,750,950}, 100};
	Academic opt{"OPT", "Health", 200, 0, {6,80,110,600,800,1000}, 100};

	blocks.emplace_back(gooseNest);
	blocks.emplace_back(ev1);
	blocks.emplace_back(needlesHall);
	blocks.emplace_back(ev2);
	blocks.emplace_back(ev3);
	blocks.emplace_back(v1);
	blocks.emplace_back(phys);
	blocks.emplace_back(b1);
	blocks.emplace_back(cif);
	blocks.emplace_back(b2);
	blocks.emplace_back(goToTims);
	blocks.emplace_back(eit);
	blocks.emplace_back(esc);
	blocks.emplace_back(slc);
	blocks.emplace_back(c2);
	blocks.emplace_back(rev);
	blocks.emplace_back(needlesHall);
	blocks.emplace_back(mc);
	blocks.emplace_back(coopFee);
	blocks.emplace_back(dc);
	blocks.emplace_back(collectOSAP);
	blocks.emplace_back(al);
	blocks.emplace_back(slc);
	blocks.emplace_back(ml);
	blocks.emplace_back(tuition);
	blocks.emplace_back(mkv);
	blocks.emplace_back(ech);
	blocks.emplace_back(needlesHall);
	blocks.emplace_back(pas);
	blocks.emplace_back(hh);
	blocks.emplace_back(timsLine);
	blocks.emplace_back(rch);
	blocks.emplace_back(pac);	
	blocks.emplace_back(dwe);
	blocks.emplace_back(cph);
	blocks.emplace_back(uwp);
	blocks.emplace_back(lhi);
	blocks.emplace_back(slc);
	blocks.emplace_back(bmh);
	blocks.emplace_back(opt);
	*/
	// create board and textdisplay
	TextDisplay td{blocks};
	Board watopoly{td};

	cout << td;

}
