//-------------------------------------------------------------------------
/* File: wavif.cpp
 * Description: "Work Around aVIF" Project (AV1 Image File Format)
 *                Container: 
 *                  ISO-BMFF (ISO Base Media File Format)
 *                    https://en.wikipedia.org/wiki/ISO/..
 *                            ..IEC_base_media_file_format
 *                  HEIF (High Efficiency Image File Format)
 *                    https://nokiatech.github.io/heif/
 *                Codec    : 
 *                  AV1
 *                    https://aomediacodec.github.io/av1-avif/
 * Authors: Bagad Sigwal
 * Copyright: 2020 Sigwal.info/github
 * Last modification: 10/03/2020
 * Version: 20.03
 *
 * Change records:
 * SWL - 09/03/2020 - creation, added main()
 * SWL - 10/03/2020 - added avifinfo()                                   */
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
//[>AVIFINFO]
//-------------------------------------------------------------------------
int avifinfo(const char *filepath){

	std::cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<std::endl;
	std::cout<<"[>AVIF FILE INFORMATIONS]"<<std::endl;
	std::cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<std::endl;
	std::cout<<"filepath: '"<<filepath<<"'"<<std::endl;
	//[af]
	std::cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<std::endl;
	std::cout<<"[<AVIF FILE INFORMATIONS]"<<std::endl;
	std::cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<std::endl;

	return 0;
}
//-------------------------------------------------------------------------
//[<AVIFINFO]
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//[>MAIN]
//-------------------------------------------------------------------------
int main(int argc, char *argv[]) {

	std::cout<<"---------------------------------------------------------------------------"<<std::endl;
	std::cout<<"[>WAVIF] version "<<WAVIF_VERSION<<std::endl;
	std::cout<<"---------------------------------------------------------------------------"<<std::endl;
	if(argc>1){
		avifinfo(argv[argc-1]);
	}
	std::cout<<"---------------------------------------------------------------------------"<<std::endl;
	std::cout<<"[<WAVIF]"<<std::endl;
	std::cout<<"---------------------------------------------------------------------------"<<std::endl;

	return 0;
}
//-------------------------------------------------------------------------
//[<MAIN]
//-------------------------------------------------------------------------
