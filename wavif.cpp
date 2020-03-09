//-------------------------------------------------------------------------
/* File: wavif.cpp
 * Description: Work on AVIF Project (AV1 Image Format)
 *                Container: HEIF (High Efficiency Image Format)
 *                  [af]
 *                Codec    : AV1
 *                  https://github.com/AOMediaCodec/av1-spec
 * Author: Bagad Sigwal
 * Copyright: 2020 Sigwal.info
 * Last modification: 09/03/2020
 * Version : 20.03
 *
 * Change records:
 * SWL - 09/03/2020 - creation, added main()                             */
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//[>DEFINITIONS]
//-------------------------------------------------------------------------
//[>STANDARD DEFINITIONS]
#include <iostream>
//[>EXTERN DEFINITIONS]
//[>PROJECT DEFINITIONS]
//[>LOCAL DEFINITIONS]
#define WAVIF_VERSION "20.03"
//-------------------------------------------------------------------------
//[<DEFINITIONS]
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//[>MAIN]
//-------------------------------------------------------------------------
int main(int argc, char *argv[]) {

	std::cout<<"---------------------------------------------------------------------------"<<std::endl;
	std::cout<<"[>WAVIF] version "<<WAVIF_VERSION<<std::endl;
	std::cout<<"---------------------------------------------------------------------------"<<std::endl;
	if(argc>1){ std::cout<<"  Arg.: x"<<argc<<std::endl; }
	// [af]
	std::cout<<"---------------------------------------------------------------------------"<<std::endl;
	std::cout<<"[<WAVIF]"<<std::endl;
	std::cout<<"---------------------------------------------------------------------------"<<std::endl;

	return 0;
}
//-------------------------------------------------------------------------
//[<MAIN]
//-------------------------------------------------------------------------
