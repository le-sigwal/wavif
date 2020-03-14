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
 * Last modification: 14/03/2020
 * Version: 20.03
 *
 * Change records:
 * SWL - 09/03/2020 - creation, added main()
 * SWL - 10/03/2020 - added avifinfo()
 * SWL - 14/03/2020 - added avifinfo/filetypebox                         */
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
//
typedef union uint32_u {
	uint32_t ui;
	char     cr[4];
} uint32_o; // octet
//-------------------------------------------------------------------------
//[<DEFINITIONS]
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//[>AVIFINFO]
//-------------------------------------------------------------------------
int avifinfo(const char *filepath){

	std::cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<std::endl;
	std::cout<<"[>AVIF FILE INFORMATIONS]"<<std::endl;
	std::cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<std::endl;
	std::cout<<"filepath: '"<<filepath<<"'"<<std::endl;

	FILE *avifile = fopen(filepath, "rt");
	if (avifile == NULL){
		return -1;
	}

	std::cout<<"  - File Type Box"<<std::endl;
	uint32_o bhsize; /*Box header size*/
	char ac=fgetc(avifile), bc=fgetc(avifile), cc=fgetc(avifile), dc=fgetc(avifile);
	bhsize.cr[0]=dc; bhsize.cr[1]=cc; bhsize.cr[2]=bc; bhsize.cr[3]=ac;
	std::cout<<"    - Box header size: "<<bhsize.ui<<std::endl;

	ac=fgetc(avifile); bc=fgetc(avifile); cc=fgetc(avifile); dc=fgetc(avifile);
	std::cout<<"    - Box header type: '"<<ac<<bc<<cc<<dc<<"'"<<std::endl;

	ac=fgetc(avifile); bc=fgetc(avifile); cc=fgetc(avifile); dc=fgetc(avifile);
	std::cout<<"    - Brand: '"<<ac<<bc<<cc<<dc<<"'"<<std::endl;

	uint32_o minvers; /*Minor version*/
	ac=fgetc(avifile); bc=fgetc(avifile); cc=fgetc(avifile); dc=fgetc(avifile);
	minvers.cr[0]=dc; minvers.cr[1]=cc; minvers.cr[2]=bc; minvers.cr[3]=ac;
	std::cout<<"    - Minor version: "<<minvers.ui<<std::endl;

	std::cout<<"    - Compatible Brands"<<std::endl;
	int cbn = (bhsize.ui-4*4)/4, cbi;
	for(cbi=0;cbi<cbn;cbi++){
		ac=fgetc(avifile); bc=fgetc(avifile); cc=fgetc(avifile); dc=fgetc(avifile);
		std::cout<<"      - '"<<ac<<bc<<cc<<dc<<"'"<<std::endl;
	}


	fclose(avifile);


	std::cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<std::endl;
	std::cout<<"[<AVIF FILE INFORMATIONS]"<<std::endl;
	std::cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<std::endl;

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
