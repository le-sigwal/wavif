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
 * Last modification: 16/03/2020
 * Version: 20.03
 *
 * Change records:
 * SWL - 09/03/2020 - creation, added main()
 * SWL - 10/03/2020 - added avifinfo()
 * SWL - 14/03/2020 - added avifinfo/filetypebox
 *                    added avifinfo/mediadatabox
 *                    added avifinfo/freespacebox
 * SWL - 15/03/2020 - added avifinfo/metabox
 *                    added avifinfo/handlerreferencebox
 *                    added avifinfo/primaryitembox
 *                    added avifinfo/itemlocationbox
 * SWL - 16/03/2020 - added avifinfo/iteminformationbox                  */
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
typedef union uint16_u {
	uint16_t ui;
	char     cr[2];
} uint16_o; // octet
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

	FILE *avifile = fopen(filepath, "rb");
	if (avifile == NULL){
		return -1;
	}

	std::cout<<"  - File Type Box"<<std::endl;
	uint32_o bhsize; /*Box header size*/
	int ica=fgetc(avifile), icb=fgetc(avifile), icc=fgetc(avifile), icd=fgetc(avifile);
	char cca=(char)ica, ccb=(char)icb, ccc=(char)icc, ccd=(char)icd;
	bhsize.cr[0]=ccd; bhsize.cr[1]=ccc; bhsize.cr[2]=ccb; bhsize.cr[3]=cca;
	std::cout<<"    - Box header size: "<<bhsize.ui<<std::endl;

	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"    - Box header type: '"<<cca<<ccb<<ccc<<ccd<<"'"<<std::endl;

	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"    - Brand: '"<<cca<<ccb<<ccc<<ccd<<"'"<<std::endl;

	uint32_o minvers; /*Minor version*/
	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	minvers.cr[0]=ccd; minvers.cr[1]=ccc; minvers.cr[2]=ccb; minvers.cr[3]=cca;
	std::cout<<"    - Minor version: "<<minvers.ui<<std::endl;

	std::cout<<"    - Compatible Brands"<<std::endl;
	int cbn = (bhsize.ui-4*4)/4, cbi;
	for(cbi=0;cbi<cbn;cbi++){
		ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
		cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
		std::cout<<"      - '"<<cca<<ccb<<ccc<<ccd<<"'"<<std::endl;
	}

	//---------------------------------------------------------------------
	std::cout<<"  - Media Data Box"<<std::endl;
	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	bhsize.cr[0]=ccd; bhsize.cr[1]=ccc; bhsize.cr[2]=ccb; bhsize.cr[3]=cca;
	std::cout<<"    - Box header size: "<<bhsize.ui<<std::endl;

	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"    - Box header type: '"<<cca<<ccb<<ccc<<ccd<<"'"<<std::endl;

	unsigned int oi, oj;
	for(oi=0;oi<(bhsize.ui-2*4);oi++){
		ica=fgetc(avifile);
	}

	//---------------------------------------------------------------------
	std::cout<<"  - Free Space Box"<<std::endl;
	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	bhsize.cr[0]=ccd; bhsize.cr[1]=ccc; bhsize.cr[2]=ccb; bhsize.cr[3]=cca;
	std::cout<<"    - Box header size: "<<bhsize.ui<<std::endl;

	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"    - Box header type: '"<<cca<<ccb<<ccc<<ccd<<"'"<<std::endl;

	std::cout<<"    - '";
	for(oi=0;oi<(bhsize.ui-2*4);oi++){
		ica=fgetc(avifile); cca=(char)ica;
		std::cout<<cca;
	}
	std::cout<<"'"<<std::endl;

	//---------------------------------------------------------------------
	//[>META BOX]
	//---------------------------------------------------------------------
	std::cout<<"  - Meta Box"<<std::endl;
	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	bhsize.cr[0]=ccd; bhsize.cr[1]=ccc; bhsize.cr[2]=ccb; bhsize.cr[3]=cca;
	std::cout<<"    - Box header size: "<<bhsize.ui<<std::endl;

	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"    - Box header type: '"<<cca<<ccb<<ccc<<ccd<<"'"<<std::endl;

	ica=fgetc(avifile);
	std::cout<<"    - Version: "<<ica<<std::endl;
	icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"    - Flags: '"<<ccb<<ccc<<ccd<<"'"<<std::endl;

	//-------------------------------------------------------------------
	std::cout<<"    - Handler Reference Box"<<std::endl;
	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	bhsize.cr[0]=ccd; bhsize.cr[1]=ccc; bhsize.cr[2]=ccb; bhsize.cr[3]=cca;
	std::cout<<"      - Box header size: "<<bhsize.ui<<std::endl;

	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"      - Box header type: '"<<cca<<ccb<<ccc<<ccd<<"'"<<std::endl;

	ica=fgetc(avifile);
	std::cout<<"      - Version: "<<ica<<std::endl;
	icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"      - Flags: '"<<ccb<<ccc<<ccd<<"'"<<std::endl;

	uint32_o pre_defined;
	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	pre_defined.cr[0]=ccd; pre_defined.cr[1]=ccc; pre_defined.cr[2]=ccb; pre_defined.cr[3]=cca;
	std::cout<<"      - pre_defined: "<<pre_defined.ui<<std::endl;

	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"      - handler_type: '"<<cca<<ccb<<ccc<<ccd<<"'"<<std::endl;

	std::cout<<"      - reserved:";
	uint32_o reserved;
	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	reserved.cr[0]=ccd; reserved.cr[1]=ccc; reserved.cr[2]=ccb; reserved.cr[3]=cca;
	std::cout<<" "<<reserved.ui;
	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	reserved.cr[0]=ccd; reserved.cr[1]=ccc; reserved.cr[2]=ccb; reserved.cr[3]=cca;
	std::cout<<", "<<reserved.ui;
	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	reserved.cr[0]=ccd; reserved.cr[1]=ccc; reserved.cr[2]=ccb; reserved.cr[3]=cca;
	std::cout<<", "<<reserved.ui<<std::endl;

	std::cout<<"      - name: '";
	for(oi=0;oi<(bhsize.ui-8*4);oi++){
		ica=fgetc(avifile); cca=(char)ica;
		std::cout<<cca;
	}
	std::cout<<"'"<<std::endl;
	//---------------------------------------------------------------------
	std::cout<<"    - Primary Item Box"<<std::endl;
	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	bhsize.cr[0]=ccd; bhsize.cr[1]=ccc; bhsize.cr[2]=ccb; bhsize.cr[3]=cca;
	std::cout<<"      - Box header size: "<<bhsize.ui<<std::endl;

	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"      - Box header type: '"<<cca<<ccb<<ccc<<ccd<<"'"<<std::endl;

	ica=fgetc(avifile); int version=ica;
	std::cout<<"      - Version: "<<version<<std::endl;
	icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"      - Flags: '"<<ccb<<ccc<<ccd<<"'"<<std::endl;

	if(version==0){
		uint16_o item_ID;
		icc=fgetc(avifile); icd=fgetc(avifile); ccc=(char)icc; ccd=(char)icd;
		item_ID.cr[0]=ccd; item_ID.cr[1]=ccc;
		std::cout<<"      - item_ID: "<<item_ID.ui<<std::endl;
	}
	else{
		uint32_o item_ID;
		ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
		cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
		item_ID.cr[0]=ccd; item_ID.cr[1]=ccc; item_ID.cr[2]=ccb; item_ID.cr[3]=cca;
		std::cout<<"      - item_ID: "<<item_ID.ui<<std::endl;
	}
	//---------------------------------------------------------------------
	std::cout<<"    - Item Location Box"<<std::endl;
	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	bhsize.cr[0]=ccd; bhsize.cr[1]=ccc; bhsize.cr[2]=ccb; bhsize.cr[3]=cca;
	std::cout<<"      - Box header size: "<<bhsize.ui<<std::endl;

	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"      - Box header type: '"<<cca<<ccb<<ccc<<ccd<<"'"<<std::endl;

	ica=fgetc(avifile); version=ica;
	std::cout<<"      - Version: "<<version<<std::endl;
	icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"      - Flags: '"<<ccb<<ccc<<ccd<<"'"<<std::endl;

	// offset_size + length_size
	ica=fgetc(avifile);
	unsigned int offset_size = (ica>>4); /* /!\ */
	std::cout<<"      - offset_size: "<<offset_size<<std::endl;
	unsigned int length_size=(ica<<28)>>28; /* /!\ */
	std::cout<<"      - length_size: "<<length_size<<std::endl;
	// base_offset_size + index_size (reserved)
	icb=fgetc(avifile);
	unsigned int base_offset_size = (icb>>4); /* /!\ */
	std::cout<<"      - base_offset_size: "<<base_offset_size<<std::endl;
	unsigned int index_size=0;
	if ((version == 1) || (version == 2)) {
		index_size=(icb<<28)>>28; /* /!\ */
		std::cout<<"      - index_size: "<<index_size<<std::endl;
	}
	int itemn=0, itemi;
	if (version < 2) {
		uint16_o item_count;
		icc=fgetc(avifile); icd=fgetc(avifile);
		ccc=(char)icc; ccd=(char)icd;
		item_count.cr[0]=ccd; item_count.cr[1]=ccc;
		std::cout<<"      - item_count: "<<item_count.ui<<std::endl;
		itemn = (int)item_count.ui;
	}
	else if (version == 2){
		uint32_o item_count;
		ica=fgetc(avifile); icb=fgetc(avifile);
		icc=fgetc(avifile); icd=fgetc(avifile);
		cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
		item_count.cr[0]=ccd; item_count.cr[1]=ccc;
		item_count.cr[2]=ccb; item_count.cr[3]=cca;
		std::cout<<"      - item_count: "<<item_count.ui<<std::endl;
		itemn = (int)item_count.ui;
	}


	for (itemi=0;itemi<itemn;itemi++) {
		if (version < 2) {
			uint16_o item_ID;
			icc=fgetc(avifile); icd=fgetc(avifile); ccc=(char)icc; ccd=(char)icd;
			item_ID.cr[0]=ccd; item_ID.cr[1]=ccc;
			std::cout<<"      - item_ID: "<<item_ID.ui<<std::endl;
		} else if (version == 2) {
			uint32_o item_ID;
			ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
			cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
			item_ID.cr[0]=ccd; item_ID.cr[1]=ccc; item_ID.cr[2]=ccb; item_ID.cr[3]=cca;
			std::cout<<"      - item_ID: "<<item_ID.ui<<std::endl;
		}
		if ((version == 1) || (version == 2)) {
			// reserved + construction_method
			ica=fgetc(avifile); icb=fgetc(avifile);
		}

		uint16_o data_reference_index;
		icc=fgetc(avifile); icd=fgetc(avifile); ccc=(char)icc; ccd=(char)icd;
		data_reference_index.cr[0]=ccd; data_reference_index.cr[1]=ccc;
		std::cout<<"      - data_reference_index: "<<
				data_reference_index.ui<<std::endl;
		/* base_offset /!\ */
		for(oi=0;oi<base_offset_size;oi++){
			ica=fgetc(avifile);
		}

		uint16_o extent_count;
		icc=fgetc(avifile); icd=fgetc(avifile); ccc=(char)icc; ccd=(char)icd;
		extent_count.cr[0]=ccd; extent_count.cr[1]=ccc;
		std::cout<<"      - extent_count: "<<extent_count.ui<<std::endl;

		for (oi=0; oi<extent_count.ui; oi++) {
			if (((version == 1) || (version == 2)) && (index_size > 0)) {
				// extent_index;
				for(oj=0;oj<index_size;oj++){ ica=fgetc(avifile); }
			}
			// extent_offset;
			for(oj=0;oj<offset_size;oj++){ ica=fgetc(avifile); }
			// extent_length;
			for(oj=0;oj<length_size;oj++){ ica=fgetc(avifile); }
		}

	}
	//---------------------------------------------------------------------
	std::cout<<"    - Item Information Box"<<std::endl;
	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	bhsize.cr[0]=ccd; bhsize.cr[1]=ccc; bhsize.cr[2]=ccb; bhsize.cr[3]=cca;
	std::cout<<"      - Box header size: "<<bhsize.ui<<std::endl;

	ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"      - Box header type: '"<<cca<<ccb<<ccc<<ccd<<"'"<<std::endl;

	ica=fgetc(avifile); version=ica;
	std::cout<<"      - Version: "<<version<<std::endl;
	icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
	ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
	std::cout<<"      - Flags: '"<<ccb<<ccc<<ccd<<"'"<<std::endl;

	itemn=0;
	if (version==0) {
		uint16_o entry_count;
		icc=fgetc(avifile); icd=fgetc(avifile); ccc=(char)icc; ccd=(char)icd;
		entry_count.cr[0]=ccd; entry_count.cr[1]=ccc;
		std::cout<<"      - entry_count: "<<entry_count.ui<<std::endl;
		itemn=(int)entry_count.ui;
	} else if (version == 2) {
		uint32_o entry_count;
		ica=fgetc(avifile); icb=fgetc(avifile); icc=fgetc(avifile); icd=fgetc(avifile);
		cca=(char)ica; ccb=(char)icb; ccc=(char)icc; ccd=(char)icd;
		entry_count.cr[0]=ccd; entry_count.cr[1]=ccc;
		entry_count.cr[2]=ccb; entry_count.cr[3]=cca;
		std::cout<<"      - entry_count: "<<entry_count.ui<<std::endl;
		itemn=(int)entry_count.ui;
	}

	for(itemi=0;itemi<itemn;itemi++){
		//[af]
	}
	//---------------------------------------------------------------------
	//[<META BOX]
	//---------------------------------------------------------------------

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
// Test files at :
//  - https://github.com/AOMediaCodec/av1-avif/tree/master/testFiles
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
