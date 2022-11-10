#ifndef MAPUNICODE_H

//
// This Program (Maping UTF-8 to Character Code) program was written by Marmayogi, Astrologer and Palmist, Sri Mahakali Jyothida Nilayam, Coimbatore, India.
// This maps utf-8 encoded string to Postscript character code (16 bit) in hexadecimal format.
// 
// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
//


#include <stddef.h>			// Refer for NULL definition 
#include <stdint.h>			// Refer for type definitions ending with _t

//Unicode mapping to Character code (2 bytes) is supported for the following Languages--------------------------
const int16_t cMaxLanguage = 12;		// English, Tamil, Hindi,		Malayalam, Telugu, Kannada,		Marathi, Gujarati,odia,		Punjabi, Bengali, Assamese
enum class ELang : char {// English, Tamil, Hindi,		Malayalam, Telugu, Kannada,		Marathi, Gujarati,odia,		Punjabi, Bengali, Assamese
	eZero = 0,
	eEnglish = 1, eEng = 1,	//  1. short form for English which is for convenience
	eTamil,					//  2. Tamil language
	eHindi,					//  3. Hindi language
	eMalayalam,				//  4. Malayalam language
	eTelugu,				//  5. Telugu language
	eKannada,				//  6. Kannada language
	eMarathi, 				//  7. Marathi language
	eGujarati, 				//  8. Gujarati language
	eOdia,					//  9. Odia language
	ePunjabi,				// 10. Punjabi language
	eBengali,				// 11. Bengali language
	eAssamese,				// 12. Assamese language
};
static const ELang aLanguage[cMaxLanguage + 1] = { ELang::eZero,
	ELang::eEnglish,	ELang::eTamil,		ELang::eHindi,				ELang::eMalayalam,  ELang::eTelugu, ELang::eKannada,
	ELang::eMarathi,	ELang::eGujarati,	ELang::eOdia,				ELang::ePunjabi,	ELang::eBengali, ELang::eAssamese,
};
static const char* asLanguage[cMaxLanguage+1] = {
	NULL,		"English",	"Tamil",	"Hindi",				"Malayalam",	"Telugu",	"Kannada",			"Marathi","Gujarati","Odia",		"Punjabi", "Bengali", "Assamese"
};

typedef struct SUnicodeBlock {
	ELang lan;									// Language supported by MY Software.
	uint32_t blockBeg;							// Beginning of Unicode Block corresponding to the laguage.
	uint32_t blockEnd;							// Beginning of Unicode Block corresponding to the laguage.
} SUnicodeBlock;
static const SUnicodeBlock aUnicode[cMaxLanguage + 1] = {
	{ELang::eZero,0},							// Zero entry
	{ELang::eEnglish,	0x0000, 0x00ff},		// Entry corresponding to Latin.
	{ELang::eTamil,		0x0B80, 0x0BFF},		// Range of Tamil Script is from 2944(U+0B80) to 3071(U+0BFF). Total 128 bytes are allocated.
	{ELang::eHindi,		0x0900, 0x097F},		// Range of Hindi Script is from 2304(U+0900) to 2431(U+097F). Total 128 bytes are allocated.
	{ELang::eMalayalam,	0x0D02, 0x0D4D},		// Range of Malayalam Script is from 3330(U+0D02) to 3405(U+0D4D) 128 code points. Number of assigned Characters are 118.
	{ELang::eTelugu,	0x0C00, 0x0C7F},		// Range of Telugu Script is from 3072(U+0C00) to 3199(U+0C7F) 128 code points. Number of assigned Characters: 98.
	{ELang::eKannada,	0x0C80, 0x0CFF},		// Range of Kannada Script is from 3200(U+0C80) to 3327(U+0CFF) 128 code points. Number of assigned Characters: 89.
	{ELang::eMarathi,	0x0900, 0x097F},		// Same as Hindi
	{ELang::eGujarati,	0x0A80, 0x0AFF},		// Range of Gujarati Script is from 2688(U+0A80) to 2815(U+0AFF) 128 code points. Number of assigned Characters: 91.
	{ELang::eOdia,		0x0B00, 0x0B7F},		// Range of Odia Script is from 2816(U+0B00) to 2943(U+0B7F) 128 code points. Number of assigned Characters: 89.
	{ELang::ePunjabi,	0x0A00, 0x0A7F},		// Range of Punjabi Script is from 2560(U+0A00) to 2687(U+0A7F) 128 code points. Number of assigned Characters: 80.
	{ELang::eBengali,	0x0980, 0x09FF},		// Range of Bengali Script is from 2432(U+0980) to 2559(U+09FF) 128 code points. Number of assigned Characters: 96.
	{ELang::eAssamese,	0x0980, 0x09FF},		// Same as Bengali
};

typedef struct SMyFont {
	short numGlyphs;							// total glyphs in the character set.
	const char *name;							// 'myNotoTamil' is the font name as indicated in Postscript procedure: /myNotoTamil {/NotoSansTamil-Regular findfont exch scalefont setfont} bind def
	const char *psname;							// Postscript font name.
	const char *fname;							// File name of the font in the disk.
} SMyFont;

enum class EMyFont : char {
	eZero = 0,
	eNoToSansTamil_Regular=1,			// Google's Tamil Font (Regular)
	eNoToSansTamil_Bold=2,				// Google's Tamil Font (Bold)
	eLatha_Regular=3,					// Microsoft's Tamil Font (Regular)
	eLatha_Bold=4,						// Microsoft's Tamil Font (Bold)
};
static const SMyFont asMyFont[cMaxLanguage + 1][10+2] = {		// Maximum 10 font files for each language are supported. If more files are there then change the number 10.
	{0,},
	// 1. English language. Entires are not allowed since this is meant for Indian Languages.
	{0,},											
	// 2. Tamil language. After all Font names are entered, terminate with Zero entry.
	{
	//	NumGlyphs	name			Postscript name					file name in the disk.
		{0,},																								// Always begins with Zero entry
		{534, "myNotoTamil",		"NotoSansTamil-Regular",		"NotoSansTamil-Regular.t42"},			// Google's Tamil Font (Regular)
		{534, "myNotoTamilBold",	"NotoSansTamil-Bold",			"NotoSansTamil-Bold.t42"},				// Google's Tamil Font (Bold)
		{434, "myLathaTamil",		"Latha",						"latha.t42"},							// Microsoft's Tamil Font (Regular)
		{434, "myLathaTamilBold",	"Latha-Bold",					"lathab.t42"},							// Microsoft's Tamil Font (Bold)
		{0},																								// Terminate with Zero entry.
	},
	// 3. Hindi language. After all Font names are entered, terminate with Zero entry.
	{
		{0,},											// Always begins with Zero entry.
		{0,},											// Terminate with Zero entry.
	},
	// 4. Malayalam language. After all Font names are entered, terminate with Zero entry.
	{
		{0,},											// Always begins with Zero entry.
		{0,},											// Terminate with Zero entry.
	},
	// 5. Telugu language. After all Font names are entered, terminate with Zero entry.
	{
		{0,},											// Always begins with Zero entry.
		{0,},											// Terminate with Zero entry.
	},
	// 6. Kannada language. After all Font names are entered, terminate with Zero entry.
	{
		{0,},											// Always begins with Zero entry.
		{0,},											// Terminate with Zero entry.
	},
	// 7. Marathi language. After all Font names are entered, terminate with Zero entry.
	{
		{0,},											// Always begins with Zero entry
		{0,},											// Terminate with Zero entry.
	},
	// 8. Gujarati language. After all Font names are entered, terminate with Zero entry.
	{
		{0,},											// Always begins with Zero entry
		{0,},											// Terminate with Zero entry.
	},
	// 9. Odia language. After all Font names are entered, terminate with Zero entry.
	{
		{0,},											// Always begins with Zero entry
		{0,},											// Terminate with Zero entry.
	},
	// 10. Punjabi language. After all Font names are entered, terminate with Zero entry.
	{
		{0,},											// Always begins with Zero entry
		{0,},											// Terminate with Zero entry.
	},
	// 11. Bengali language. After all Font names are entered, terminate with Zero entry.
	{
		{0,},											// Always begins with Zero entry
		{0,},											// Terminate with Zero entry.
	},
	// 12. Assamese language. After all Font names are entered, terminate with Zero entry.
	{
		{0,},											// Always begins with Zero entry
		{0,},											// Terminate with Zero entry.
	},
};
// This maps unicode to CID
// NotoSansTamil-Regular Font (Google)
static const short aNotoSansTamilMap[] = {	
// 0 - 127 glyphs														R     R		ஂ		ஃ			R		அ		ஆ		இ		ஈ	உ		ஊ		R			R		R		எ		ஏ
	0,0,4,5,		0,6,7,8,		9,10,11,0,		0,0,12,13,		// U+0B80,U+0B81,U+0B82,U+0B83,		U+0B84,U+0B85,U+0B86,U+0B87,	U+0B88,U+0B89,U+0B8A,U+0B8B,	U+0B8C,U+0B8D,U+0B8E,U+0B8F,		
//																		ஐ		R		ஒ		ஓ		ஔ		க		R		R		R		ங		ச		R		ஜ		R		ஞ		ட
	14,0,15,16,		17,18,0,0,		0,19,20,0,		21,0,22,23,		// U+0B90,U+0B91,U+0B92,U+0B93,		U+0B94,U+0B95,U+0B96,U+0B97,	U+0B98,U+0B99,U+0B9A,U+0B9B,	U+0B9C,U+0B9D,U+0B9E,U+0B9F,		
//																		R		R		R		ண		த		R		R		R		ந		ன		ப		R		R		R		ம		ய
	0,0,0,24,		25,0,0,0,		26,27,28,0,		0,0,29,30,		// U+0BA0,U+0BA1,U+0BA2,U+0BA3,		U+0BA4,U+0BA5,U+0BA6,U+0BA7,	U+0BA8,U+0BA9,U+0BAA,U+0BAB,	U+0BAC,U+0BAD,U+0BAE,U+0BAF,		
//																		ர		ற		ல		ள		ழ		வ		ஶ		ஷ		ஸ		ஹ		R		R		R		R		ா		ி
	31,32,33,34,	35,36,37,38,	39,40,0,0,		0,0,41,42,		// U+0BB0,U+0BB1,U+0BB2,U+0BB3,		U+0BB4,U+0BB5,U+0BB6,U+0BB7,	U+0BB8,U+0BB9,U+0BBA,U+0BBB,	U+0BBC,U+0BBD,U+0BBE,U+0BBF,		
//																		ீ		ு		ூ		R		R		R		ெ		ே		ை		R		ொ		ோ		ௌ	்		R		R
	43,44,45,0,		0,0,46,47,		48,0,49,50,		51,52,0,0,		// U+0BC0,U+0BC1,U+0BC2,U+0BC3,		U+0BC4,U+0BC5,U+0BC6,U+0BC7,	U+0BC8,U+0BC9,U+0BCA,U+0BCB,	U+0BCC,U+0BCD,U+0BCE,U+0BCF,		
//																		ௐ		R		R		R		R		R		R		ௗ		R		R		R		R		R		R		R		R
	53,0,0,0,		0,0,0,54,		0,0,0,0,		0,0,0,0,		// U+0BD0,U+0BD1,U+0BD2,U+0BD3,		U+0BD4,U+0BD5,U+0BD6,U+0BD7,	U+0BD8,U+0BD9,U+0BDA,U+0BDB,	U+0BDC,U+0BDD,U+0BDE,U+0BDF,		
//																		R		R		R		R		R		R		௦		௧		௨		௩		௪		௫		௬		௭		௮		௯
	0,0,0,0,		0,0,55,56,		57,58,59,60,	61,62,63,64,	// U+0BE0,U+0BE1,U+0BE2,U+0BE3,		U+0BE4,U+0BE5,U+0BE6,U+0BE7,	U+0BE8,U+0BE9,U+0BEA,U+0BEB,	U+0BEC,U+0BED,U+0BEE,U+0BEF,		
//																		௰		௱		௲		௳		௴		௵		௶		௷		௸		௹		௺		R		R		R		R		R	
	65,66,67,68,	69,70,71,72,	73,74,75,0,		0,0,0,0,		// U+0BF0,U+0BF1,U+0BF2,U+0BF3,		U+0BF4,U+0BF5,U+0BF6,U+0BF7,	U+0BF8,U+0BF9,U+0BFA,U+0BFB,	U+0BFC,U+0BFD,U+0BFE,U+0BFF,		

// 128 - 271 glyphs	(144 placeholders but 94 valid glyps) Ligature
	76,77,78,79,		80,81,82,83,		84,85,86,87,		88,89,90,91,		// க்ஷ,க்,ங்,ச்,			ஜ்,ஞ்,ட்,ண்,			த்,ந்,ன்,ப்,						ம்,ய்,ர்,ற்,
	92,93,94,95,		96,97,98,99,		100,0,0,0,			0,0,0,0,			// ல்,ள்,ழ்,வ்,			ஶ்,ஷ்,ஸ்,ஹ்,			க்ஷ்,
//																					   ....க.....			....ங....				....ச....						.....ஜ....
	0,101,102,103,		0,104,105,106,		0,107,108,109,		0,110,0,0,			// கி,கீ,கு,கூ,			ஙி,ஙீ,ஙு,ஙூ,			சி,சீ,சு,சூ,						ஜி,ஜீ,ஜு,ஜூ
//																					   ....ஞ....			....ட....				....ண....						....த....
	0,111,112,113,		114,115,116,117,	0,118,119,120,		0,121,122,123,		// ஞி,ஞீ,ஞு,ஞூ,		டி,டீ,டு,டூ,				ணி,ணீ,ணு,ணூ,				தி,தீ,து,தூ,
//																					   ....ந....			....ன....				....ப....						....ம....
	0,124,125,126,		0,127,128,129,		0,130,131,132,		0,133,134,135,		// நி,நீ,நு,நூ,			னி,னீ,னு,னூ,			பி,பீ,பு,பூ,						மி,மீ,மு,மூ,
//																					   ....ய....			....ர....				....ற....						....ல....
	0,136,137,138,		0,139,140,141,		0,142,143,144,		145,146,147,148,	// யி,யீ,யு,யூ,			ரி,ரீ,ரு,ரூ,				றி,றீ,று,றூ,					லி,லீ,லு,லூ,
//																					   ....ள....			....ழ....				....வ....						......ஶ......
	0,149,150,151,		0,152,153,154,		0,155,156,157,		0,0,0,0,			// ளி,ளீ,ளு,ளூ,		ழி,ழீ,ழு,ழூ,			வி,வீ,வு,வூ,					ஶி,ஶீ,ஶு,ஶூ					
//																					   ....ஷ....			....ஸ....				....ஹ....						....க்ஷ....			
	0,158,0,0,			159,160,0,0,		0,161,0,0,			0,162,0,0,			// ஷி,ஷீ,ஷு,ஷூ,	ஸி,ஸீ,ஸு,ஸூ,		ஹி,ஹீ,ஹு,ஹூ				க்ஷி,க்ஷீ,க்ஷு,க்ஷூ,			
	163,164,165,166,	167,168,169,0,		0,0,0,0,			0,0,0,0,			// ஸ்ரீ,sym,sym,sym,		sym,sym,sym,unused		unused,unused,unused,unused		unused,unused,unused,unused

// 	Basic Latin (272 - 399) (128 glyphs)-------------
// 	                                																																							CR	
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,2,0,0,			// U+0000,U+0001,U+0002,U+0003,		U+0004,U+0005,U+0006,U+0007,	U+0008,U+0009,U+000A,U+000B,	U+000C,U+000D,U+000E,U+000F,
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+0010,U+0011,U+0012,U+0013,		U+0014,U+0015,U+0016,U+0017,	U+0018,U+0019,U+001A,U+001B,	U+001C,U+001D,U+001E,U+001F,		
//																						Space	!		"		#		$		%		&		'		(		)		*		+		,		-		.		/
	3,170,171,172,		504,173,496,174,	175,176,177,178,	179,180,181,182,	// U+0020,U+0021,U+0022,U+0023,		U+0024,U+0025,U+0026,U+0027,	U+0028,U+0029,U+002A,U+002B,	U+002C,U+002D,U+002E,U+002F,
//																						0		1		2		3		4		5		6		7		8		9		:		;		<		=		>		?
	183,184,185,186,	187,188,189,190,	191,192,193,194,	195,196,197,198,	// U+0030,U+0031,U+0032,U+0033,		U+0034,U+0035,U+0036,U+0037,	U+0038,U+0039,U+003A,U+003B,	U+003C,U+003D,U+003E,U+003F,
//																						@		A		B		C		D		E		F		G		H		I		J		K		L		M		N		O
	495,256,268,269,	274,278,287,288,	292,294,303,304,	306,311,312,318,	// U+0040,U+0041,U+0042,U+0043,		U+0044,U+0045,U+0046,U+0047,	U+0048,U+0049,U+004A,U+004B,	U+004C,U+004D,U+004E,U+004F,
//																						P		Q		R		S		T		U		V		W		X		Y		Z		[		\		]		^		_		`
	328,330,331,335,	341,344,354,355,	360,361,366,199,	200,201,202,203,	// U+0050,U+0051,U+0052,U+0053,		U+0054,U+0055,U+0056,U+0057,	U+0058,U+0059,U+005A,U+005B,	U+005C,U+005D,U+005E,U+005F,
//																						`		a		b		c		d		e		f		g		h		i		j		k		l		m		n		o
	519,370,382,383,	388,392,401,402,	406,408,417,419,	421,426,427,433,	// U+0060,U+0061,U+0062,U+0063,		U+0064,U+0065,U+0066,U+0067,	U+0068,U+0069,U+006A,U+006B,	U+006C,U+006D,U+006E,U+006F,
//																						p		q		r		s		t		u		v		w		x		y		z		{		|		}		~		Del	
	443,445,446,450,	456,459,469,470,	475,476,481,204,	205,206,207,208,	// U+0070,U+0071,U+0072,U+0073,		U+0074,U+0075,U+0076,U+0077,	U+0078,U+0079,U+007A,U+007B,	U+007C,U+007D,U+007E,U+007F,

// Latin-1 Supplement (400 - 527) (128 glyphs)-------------
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+0080,U+0081,U+0082,U+0083,		U+0084,U+0085,U+0086,U+0087,	U+0088,U+0089,U+008A,U+008B,	U+008C,U+008D,U+008E,U+008F,		
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+0090,U+0091,U+0092,U+0093,		U+0094,U+0095,U+0096,U+0097,	U+0098,	U+0099,U+009A,U+009B,	U+009C,U+009D,U+009E,U+009F,	
//																								¡		¢		£		¤		¥		¦		§		¨		©		ª		«		¬				®		¯	
	0,487,503,506,		0,507,0,498,		518,499,0,248,		0,0,500,527,		// U+00A0,U+00A1,U+00A2,U+00A3,		U+00A4,U+00A5,U+00A6,U+00A7,	U+00A8,U+00A9,U+00AA,U+00AB,	U+00AC,U+00AD,U+00AE,U+00AF,	
//																						°		±		²		³		´		µ		¶		·		¸		¹		º		»		¼		½		¾		¿	
	502,0,233,234,		520,0,497,489,		528,0,486,249,		0,0,0,488,			// U+00B0,U+00B1,U+00B2,U+00B3,		U+00B4,U+00B5,U+00B6,U+00B7,	U+00B8,U+00B9,U+00BA,U+00BB,	U+00BC,U+00BD,U+00BE,U+00BF,		
//																						À		Á		Â		Ã		Ä		Å		Æ		Ç		È		É		Ê		Ë		Ì		Í		Î		Ï
	262,257,260,266,	261,265,267,272,	284,279,281,282,	300,296,297,298,	// U+00C0,U+00C1,U+00C2,U+00C3,		U+00C4,U+00C5,U+00C6,U+00C7,	U+00C8,U+00C9,U+00CA,U+00CB,	U+00CC,	U+00CD,U+00CE,U+00CF,		
//																						Ð		Ñ		Ò		Ó		Ô		Õ		Ö		×		Ø		Ù		Ú		Û		Ü		Ý		Þ		ß	
	275,316,322,319,	320,326,321,0,		325,349,345,347,	348,362,329,455,	// U+00D0,U+00D1,U+00D2,U+00D3,		U+00D4,U+00D5,U+00D6,U+00D7,	U+00D8,U+00D9,U+00DA,U+00DB,	U+00DC,U+00DD,U+00DE,U+00DF,	
//																						à		á		â		ã		ä		å		æ		ç		è		é		ê		ë		ì		í		î		ï	
	376,371,374,380,	375,379,381,386,	398,393,395,396,	413,410,411,412,	// U+00E0,U+00E1,U+00E2,U+00E3,		U+00E4,U+00E5,U+00E6,U+00E7,	U+00E8,U+00E9,U+00EA,U+00EB,	U+00EC,U+00ED,U+00EE,U+00EF,	
//																						ð		ñ		ò		ó		ô		õ		ö		÷		ø		ù		ú		û		ü		ý		þ		ÿ	
	0,431,437,434,		435,441,436,0,		440,464,460,462,	463,477,444,479,	// U+00F0,U+00F1,U+00F2,U+00F3,		U+00F4,U+00F5,U+00F6,U+00F7,	U+00F8,U+00F9,U+00FA,U+00FB,	U+00FC,U+00FD,U+00FE,U+00FF,		

// Latin Extended-A (528 - 655) (128 glyphs)-------------
//																						Ā		ā		Ă		ă		Ą		ą		Ć		ć		Ĉ		ĉ		Ċ		ċ		Č		č		Ď		ď		
	263,377,258,372,	264,378,270,384,	0,0,273,387,		271,385,276,390,	// U+0100,U+0101,U+0102,U+0103,		U+0104,U+0105,U+0106,U+0107,	U+0108,	U+0109,U+010A,U+010B,	U+010C,U+010D,U+010E,U+010F,		
//																						Đ		đ		Ē		ē		Ĕ		ĕ		Ė		ė		Ę		ę		Ě		ě		Ĝ		ĝ		Ğ		ğ
	277,391,285,399,	0,0,283,397,		286,400,0,394,		0,0,289,403,		// U+0110,U+0111,U+0112,U+0113,		U+0114,U+0115,U+0116,U+0117,	U+0118,U+0119,U+011A,U+011B,	U+011C,U+011D,U+011E,U+011F,		
//																						Ġ		ġ		Ģ		ģ		Ĥ		ĥ		Ħ		ħ		Ĩ		ĩ		Ī		ī		Ĭ		ĭ		Į		į
	291,405,290,404,	0,0,293,407,		0,0,301,415,		0,0,302,416,		// U+0120,U+0121,U+0122,U+0123,		U+0124,U+0125,U+0126,U+0127,	U+0128,U+0129,U+012A,U+012B,	U+012C,U+012D,U+012E,U+012F,		
//																						İ		ı		Ĳ		ĳ		Ĵ		ĵ		Ķ		ķ		ĸ		Ĺ		ĺ		Ļ		ļ		Ľ		ľ		Ŀ
	299,409,295,0,		0,0,305,420,		0,307,422,414,		424,0,423,0,		// U+0130,U+0131,U+0132,U+0133,		U+0134,U+0135,U+0136,U+0137,	U+0138,U+0139,U+013A,U+013B,	U+013C,U+013D,U+013E,U+013F,	
//																						ŀ		Ł		ł		Ń		ń		Ņ		ņ		Ň		ň		ŉ		Ŋ		ŋ		Ō		ō		Ŏ		ŏ
	0,0,425,313,		428,315,430,314,	429,0,317,432,		324,439,0,0,		// U+0140,U+0141,U+0142,U+0143,		U+0144,U+0145,U+0146,U+0147,	U+0148,U+0149,U+014A,U+014B,	U+014C,U+014D,U+014E,U+014F,		
//																						Ő		ő		Œ		œ		Ŕ		ŕ		Ŗ		ŗ		Ř		ř		Ś		ś		Ŝ		ŝ		Ş		ş
	323,438,327,442,	332,447,334,449,	333,448,336,451,	0,0,338,453,		// U+0150,U+0151,U+0152,U+0153,		U+0154,U+0155,U+0156,U+0157,	U+0158,U+0159,U+015A,U+015B,	U+015C,U+015D,U+015E,U+015F,	
//																						Š		š		Ţ		ţ		Ť		ť		Ŧ		ŧ		Ũ		ũ		Ū		ū		Ŭ		ŭ		Ů		ů
	337,452,0,0,		342,457,0,0,		0,0,351,466,		346,461,353,468,	// U+0160,U+0161,U+0162,U+0163,		U+0164,U+0165,U+0166,U+0167,	U+0168,U+0169,U+016A,U+016B,	U+016C,U+016D,U+016E,U+016F,		
//																						Ű		ű		Ų		ų		Ŵ		ŵ		Ŷ		ŷ		Ÿ		Ź		ź		Ż		ż		Ž		ž		ſ		
	350,465,352,467,	357,472,363,478,	364,367,482,369,	484,368,483,0,		// U+0170,U+0171,U+0172,U+0173,		U+0174,U+0175,U+0176,U+0177,	U+0178,U+0179,U+017A,U+017B,	U+017C,U+017D,U+017E,U+017F,	


// General Punctuation (656 - 767) (112 glyphs)-------------
//																						
	0,0,0,0,			0,0,0,0,			0,0,0,239,			240,241,0,0,		// U+2000,U+2001,U+2002,U+2003,		U+2004,U+2005,U+2006,U+2007,	U+2008,	U+2009,U+200A,U+200B,	U+200C,U+200D,U+200E,U+200F,		
//																						‐		‑		‒		–		—		―		‖		‗		‘		’		‚		‛		“		”		„		‟
	242,0,0,210,		211,0,0,0,			212,213,491,0,		214,215,492,0,		// U+2010,U+2011,U+2012,U+2013,		U+2014,U+2015,U+2016,U+2017,	U+2018,U+2019,U+201A,U+201B,	U+201C,U+201D,U+201E,U+201F,		
//																						†		‡		•		‣		․		‥		…		‧										
	0,0,490,0,			0,0,216,0,			0,0,0,0,			0,0,0,0,			// U+2020,U+2021,U+2022,U+2023,		U+2024,U+2025,U+2026,U+2027,	U+2028,U+2029,U+202A,U+202B,	U+202C,U+202D,U+202E,U+202F,		
//																						‰		‱		′		″		‴		‵		‶		‷		‸		‹		›		※		‼		‽		‾		‿
	0,0,0,0,			0,0,0,0,			0,493,494,0,		0,0,0,0,			// U+2030,U+2031,U+2032,U+2033,		U+2034,U+2035,U+2036,U+2037,	U+2038,U+2039,U+203A,U+203B,	U+203C,U+203D,U+203E,U+203F,	
//																						⁀		⁁		⁂		⁃		⁄		⁅		⁆		⁇		⁈		⁉		⁊		⁋		⁍		⁎		⁏
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+2040,U+2041,U+2042,U+2043,		U+2044,U+2045,U+2046,U+2047,	U+2048,U+2049,U+204A,U+204B,	U+204C,U+204D,U+204E,U+204F,		
//																						⁐		⁑		⁒		⁓		⁔		⁕		⁖		⁗		⁘		⁙		⁚		⁛		⁜		⁝		⁞
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+2050,U+2051,U+2052,U+2053,		U+2054,U+2055,U+2056,U+2057,	U+2058,U+2059,U+205A,U+205B,	U+205C,U+205D,U+205E,U+205F,	
//																						
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+2060,U+2061,U+2062,U+2063,		U+2064,U+2065,U+2066,U+2067,	U+2068,U+2069,U+206A,U+206B,	U+206C,U+206D,U+206E,U+206F,		

// Currency Symbols (768 - 815) (48 glyphs)-------------
//																						₠		₡		₢		₣		₤		₥		₦		₧		₨		₩		₪		₫		€		₭		₮		₯	
	0,0,0,0,			0,0,0,0,			0,0,0,0,			505,0,0,0,			// U+20A0,U+20A1,U+20A2,U+20A3,		U+20A4,U+20A5,U+20A6,U+20A7,	U+20A8,U+20A9,U+20AA,U+20AB,	U+20AC,U+20AD,U+20AE,U+20AF,	
//																						₰		₱		₲		₳		₴		₵		₶		₷		₸		₹		₺		₻		₼		₽		₾		₿	
	0,0,0,0,			0,0,0,0,			0,220,0,0,			0,0,0,0,			// U+20B0,U+20B1,U+20B2,U+20B3,		U+20B4,U+20B5,U+20B6,U+20B7,	U+20B8,U+20B9,U+20BA,U+20BB,	U+20BC,U+20BD,U+20BE,U+20BF,		
//																						
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+20C0,U+20C1,U+20C2,U+20C3,		U+20C4,U+20C5,U+20C6,U+20C7,	U+20C8,U+20C9,U+20CA,U+20CB,	U+20CC,	U+20CD,U+20CE,U+20CF,		
//																						Ð		Ñ		Ò		Ó		Ô		Õ		Ö		×		Ø		Ù		Ú		Û		Ü		Ý		Þ		ß	

};

// Latha Font (Microsoft)
static const short aLathaTamilMap[] = {	
// 0 - 127 glyphs														R     R		ஂ		ஃ			R		அ		ஆ		இ		ஈ	உ		ஊ		R			R		R		எ		ஏ
	0,0,52,53,		0,54,55,56,		57,58,59,0,		0,0,60,61,		// U+0B80,U+0B81,U+0B82,U+0B83,		U+0B84,U+0B85,U+0B86,U+0B87,	U+0B88,U+0B89,U+0B8A,U+0B8B,	U+0B8C,U+0B8D,U+0B8E,U+0B8F,		
//																		ஐ		R		ஒ		ஓ		ஔ		க		R		R		R		ங		ச		R		ஜ		R		ஞ		ட
	62,0,63,64,		65,66,0,0,		0,67,68,0,		69,0,70,71,		// U+0B90,U+0B91,U+0B92,U+0B93,		U+0B94,U+0B95,U+0B96,U+0B97,	U+0B98,U+0B99,U+0B9A,U+0B9B,	U+0B9C,U+0B9D,U+0B9E,U+0B9F,		
//																		R		R		R		ண		த		R		R		R		ந		ன		ப		R		R		R		ம		ய
	0,0,0,72,		73,0,0,0,		74,75,76,0,		0,0,77,78,		// U+0BA0,U+0BA1,U+0BA2,U+0BA3,		U+0BA4,U+0BA5,U+0BA6,U+0BA7,	U+0BA8,U+0BA9,U+0BAA,U+0BAB,	U+0BAC,U+0BAD,U+0BAE,U+0BAF,		
//																		ர		ற		ல		ள		ழ		வ		ஶ		ஷ		ஸ		ஹ		R		R		R		R		ா		ி
	79,80,81,82,	83,84,431,85,	86,87,0,0,		0,0,88,89,		// U+0BB0,U+0BB1,U+0BB2,U+0BB3,		U+0BB4,U+0BB5,U+0BB6,U+0BB7,	U+0BB8,U+0BB9,U+0BBA,U+0BBB,	U+0BBC,U+0BBD,U+0BBE,U+0BBF,		
//																		ீ		ு		ூ		R		R		R		ெ		ே		ை		R		ொ	ோ	ௌ	்		R		R
	90,91,92,0,		0,0,93,94,		95,0,96,97,		98,99,0,0,		// U+0BC0,U+0BC1,U+0BC2,U+0BC3,		U+0BC4,U+0BC5,U+0BC6,U+0BC7,	U+0BC8,U+0BC9,U+0BCA,U+0BCB,	U+0BCC,U+0BCD,U+0BCE,U+0BCF,		
//																		ௐ		R		R		R		R		R		R		ௗ		R		R		R		R		R		R		R		R
	139,0,0,0,		0,0,0,100,		0,0,0,0,		0,0,0,0,		// U+0BD0,U+0BD1,U+0BD2,U+0BD3,		U+0BD4,U+0BD5,U+0BD6,U+0BD7,	U+0BD8,U+0BD9,U+0BDA,U+0BDB,	U+0BDC,U+0BDD,U+0BDE,U+0BDF,		
//																		R		R		R		R		R		R		௦		௧		௨		௩		௪		௫		௬		௭		௮		௯
	0,0,0,0,0,0,430,101,	102,103,104,105,	106,107,108,109,	// U+0BE0,U+0BE1,U+0BE2,U+0BE3,		U+0BE4,U+0BE5,U+0BE6,U+0BE7,	U+0BE8,U+0BE9,U+0BEA,U+0BEB,	U+0BEC,U+0BED,U+0BEE,U+0BEF,		
//																		௰		௱		௲		௳		௴		௵	௶		௷		௸		௹		௺		R		R		R		R		R	
	110,111,112,194,	195,196,197,198,	199,200,201,0,0,0,0,0,	// U+0BF0,U+0BF1,U+0BF2,U+0BF3,		U+0BF4,U+0BF5,U+0BF6,U+0BF7,	U+0BF8,U+0BF9,U+0BFA,U+0BFB,	U+0BFC,U+0BFD,U+0BFE,U+0BFF,		

// 128 - 271 glyphs	(144 placeholders but 82 valid glyps) Ligature
	113,116,117,118,	119,120,121,122,	123,124,125,126,	127,128,129,130,	// க்ஷ,க்,ங்,ச்,			ஜ்,ஞ்,ட்,ண்,			த்,ந்,ன்,ப்,				ம்,ய்,ர்,ற்,
	131,132,133,134,	432,135,136,137,	138,0,0,0,			0,0,0,0,			// ல்,ள்,ழ்,வ்,			ஶ்,ஷ்,ஸ்,ஹ்,			க்ஷ்,
//																					   ....க.....			....ங....				....ச....				.....ஜ....
	0,0,148,149,		0,0,150,151,		0,0,152,153,		0,0,0,0,			// கி,கீ,கு,கூ,			ஙி,ஙீ,ஙு,ஙூ,			சி,சீ,சு,சூ,				ஜி,ஜீ,ஜு,ஜூ
//																					   ....ஞ....			....ட....				....ண....				....த....
	0,0,154,155,		156,157,158,159,	0,0,160,161,		0,0,162,163,		// ஞி,ஞீ,ஞு,ஞூ,		டி,டீ,டு,டூ,				ணி,ணீ,ணு,ணூ,		தி,தீ,து,தூ,
//																					   ....ந....			....ன....				....ப....				....ம....
	0,0,164,165,		0,0,167,168,		0,0,169,170,		0,0,171,172,		// நி,நீ,நு,நூ,			னி,னீ,னு,னூ,			பி,பீ,பு,பூ,				மி,மீ,மு,மூ,
//																					   ....ய....			....ர....				....ற....				....ல....
	0,0,173,174,		190,191,175,176,	0,0,178,179,		0,426,180,181,		// யி,யீ,யு,யூ,			ரி,ரீ,ரு,ரூ,				றி,றீ,று,றூ,			லி,லீ,லு,லூ,
//																					   ....ள....			....ழ....				....வ....				....ஶ....			
	0,0,182,183,		0,0,184,185,		0,0,186,187,		0,0,0,0,			// ளி,ளீ,ளு,ளூ,		ழி,ழீ,ழு,ழூ,			வி,வீ,வு,வூ,			ஶி,ஶீ,ஶு,ஶூ					
//																					   ....ஷ....			....ஸ....				....ஹ....				....க்ஷ....			
	0,0,0,0,			0,425,0,0,			0,0,0,0,			0,0,0,0,			// ஷி,ஷீ,ஷு,ஷூ,	ஸி,ஸீ,ஸு,ஸூ,		ஹி,ஹீ,ஹு,ஹூ		க்ஷி,க்ஷீ,க்ஷு,க்ஷூ,	 		
	188,427,428,429,	166,424,177,140,	141,142,143,144,	145,146,147,0,		// ஸ்ரீ, ர், ரி, ரீ,	   naa, nnaa, raa,sym,		sym,sym,sym,sym,		sym,sym,sym,unused	

// 	Basic Latin (272 - 399) (128 glyphs)-------------
// 	                                																																							CR	
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,2,0,0,			// U+0000,U+0001,U+0002,U+0003,		U+0004,U+0005,U+0006,U+0007,	U+0008,U+0009,U+000A,U+000B,	U+000C,U+000D,U+000E,U+000F,
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+0010,U+0011,U+0012,U+0013,		U+0014,U+0015,U+0016,U+0017,	U+0018,U+0019,U+001A,U+001B,	U+001C,U+001D,U+001E,U+001F,		
//																						Space	!		"		#		$		%		&		'		(		)		*		+		,		-		.		/
	202,203,204,205,	206,207,208,209,	210,211,212,213,	214,215,216,217,	// U+0020,U+0021,U+0022,U+0023,		U+0024,U+0025,U+0026,U+0027,	U+0028,U+0029,U+002A,U+002B,	U+002C,U+002D,U+002E,U+002F,
//																						0		1		2		3		4		5		6		7		8		9		:		;		<		=		>		?
	218,219,220,221,	222,223,224,225,	226,227,228,229,	230,231,232,233,	// U+0030,U+0031,U+0032,U+0033,		U+0034,U+0035,U+0036,U+0037,	U+0038,U+0039,U+003A,U+003B,	U+003C,U+003D,U+003E,U+003F,
//																						@		A		B		C		D		E		F		G		H		I		J		K		L		M		N		O
	234,235,236,237,	238,239,240,241,	242,243,244,245,	246,247,248,249,	// U+0040,U+0041,U+0042,U+0043,		U+0044,U+0045,U+0046,U+0047,	U+0048,U+0049,U+004A,U+004B,	U+004C,U+004D,U+004E,U+004F,
//																						P		Q		R		S		T		U		V		W		X		Y		Z		[		\		]		^		_		`
	250,251,252,253,	254,255,256,257,	258,259,260,261,	262,263,264,265,	// U+0050,U+0051,U+0052,U+0053,		U+0054,U+0055,U+0056,U+0057,	U+0058,U+0059,U+005A,U+005B,	U+005C,U+005D,U+005E,U+005F,
//																						`		a		b		c		d		e		f		g		h		i		j		k		l		m		n		o
	266,267,268,269,	270,271,272,273,	274,275,276,277,	278,279,280,281,	// U+0060,U+0061,U+0062,U+0063,		U+0064,U+0065,U+0066,U+0067,	U+0068,U+0069,U+006A,U+006B,	U+006C,U+006D,U+006E,U+006F,
//																						p		q		r		s		t		u		v		w		x		y		z		{		|		}		~		Del	
	282,283,284,285,	286,287,288,289,	290,291,292,293,	294,295,296,0,		// U+0070,U+0071,U+0072,U+0073,		U+0074,U+0075,U+0076,U+0077,	U+0078,U+0079,U+007A,U+007B,	U+007C,U+007D,U+007E,U+007F,
// Latin-1 Supplement (400 - 527) (128 glyphs)-------------
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+0080,U+0081,U+0082,U+0083,		U+0084,U+0085,U+0086,U+0087,	U+0088,U+0089,U+008A,U+008B,	U+008C,U+008D,U+008E,U+008F,		
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+0090,U+0091,U+0092,U+0093,		U+0094,U+0095,U+0096,U+0097,	U+0098,	U+0099,U+009A,U+009B,	U+009C,U+009D,U+009E,U+009F,	
//																								¡		¢		£		¤		¥		¦		§		¨		©		ª		«		¬				®		¯	
	0,324,325,326,		327,328,329,330,	331,332,333,334,	335,336,337,338,	// U+00A0,U+00A1,U+00A2,U+00A3,		U+00A4,U+00A5,U+00A6,U+00A7,	U+00A8,U+00A9,U+00AA,U+00AB,	U+00AC,U+00AD,U+00AE,U+00AF,	
//																						°		±		²		³		´		µ		¶		·		¸		¹		º		»		¼		½		¾		¿	
	339,340,341,342,	343,344,345,346,	347,348,349,350,	351,352,353,354,	// U+00B0,U+00B1,U+00B2,U+00B3,		U+00B4,U+00B5,U+00B6,U+00B7,	U+00B8,U+00B9,U+00BA,U+00BB,	U+00BC,U+00BD,U+00BE,U+00BF,		
//																						À		Á		Â		Ã		Ä		Å		Æ		Ç		È		É		Ê		Ë		Ì		Í		Î		Ï
	355,356,357,358,	359,360,361,362,	363,364,365,366,	367,368,369,370,	// U+00C0,U+00C1,U+00C2,U+00C3,		U+00C4,U+00C5,U+00C6,U+00C7,	U+00C8,U+00C9,U+00CA,U+00CB,	U+00CC,	U+00CD,U+00CE,U+00CF,		
//																						Ð		Ñ		Ò		Ó		Ô		Õ		Ö		×		Ø		Ù		Ú		Û		Ü		Ý		Þ		ß	
	371,372,373,374,	375,376,377,378,	379,380,381,382,	383,384,385,386,	// U+00D0,U+00D1,U+00D2,U+00D3,		U+00D4,U+00D5,U+00D6,U+00D7,	U+00D8,U+00D9,U+00DA,U+00DB,	U+00DC,U+00DD,U+00DE,U+00DF,	
//																						à		á		â		ã		ä		å		æ		ç		è		é		ê		ë		ì		í		î		ï	
	387,388,389,390,	391,392,393,394,	395,396,397,398,	399,400,401,402,	// U+00E0,U+00E1,U+00E2,U+00E3,		U+00E4,U+00E5,U+00E6,U+00E7,	U+00E8,U+00E9,U+00EA,U+00EB,	U+00EC,U+00ED,U+00EE,U+00EF,	
//																						ð		ñ		ò		ó		ô		õ		ö		÷		ø		ù		ú		û		ü		ý		þ		ÿ	
	403,404,405,406,	407,408,409,410,	411,412,413,414,	415,416,417,418,	// U+00F0,U+00F1,U+00F2,U+00F3,		U+00F4,U+00F5,U+00F6,U+00F7,	U+00F8,U+00F9,U+00FA,U+00FB,	U+00FC,U+00FD,U+00FE,U+00FF,		
// Latin Extended-A (528 - 655) (128 glyphs)-------------
//																						Ā		ā		Ă		ă		Ą		ą		Ć		ć		Ĉ		ĉ		Ċ		ċ		Č		č		Ď		ď		
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+0100,U+0101,U+0102,U+0103,		U+0104,U+0105,U+0106,U+0107,	U+0108,	U+0109,U+010A,U+010B,	U+010C,U+010D,U+010E,U+010F,		
//																						Đ		đ		Ē		ē		Ĕ		ĕ		Ė		ė		Ę		ę		Ě		ě		Ĝ		ĝ		Ğ		ğ
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+0110,U+0111,U+0112,U+0113,		U+0114,U+0115,U+0116,U+0117,	U+0118,U+0119,U+011A,U+011B,	U+011C,U+011D,U+011E,U+011F,		
//																						Ġ		ġ		Ģ		ģ		Ĥ		ĥ		Ħ		ħ		Ĩ		ĩ		Ī		ī		Ĭ		ĭ		Į		į
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+0120,U+0121,U+0122,U+0123,		U+0124,U+0125,U+0126,U+0127,	U+0128,U+0129,U+012A,U+012B,	U+012C,U+012D,U+012E,U+012F,		
//																						İ		ı		Ĳ		ĳ		Ĵ		ĵ		Ķ		ķ		ĸ		Ĺ		ĺ		Ļ		ļ		Ľ		ľ		Ŀ
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+0130,U+0131,U+0132,U+0133,		U+0134,U+0135,U+0136,U+0137,	U+0138,U+0139,U+013A,U+013B,	U+013C,U+013D,U+013E,U+013F,	
//																						ŀ		Ł		ł		Ń		ń		Ņ		ņ		Ň		ň		ŉ		Ŋ		ŋ		Ō		ō		Ŏ		ŏ
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+0140,U+0141,U+0142,U+0143,		U+0144,U+0145,U+0146,U+0147,	U+0148,U+0149,U+014A,U+014B,	U+014C,U+014D,U+014E,U+014F,		
//																						Ő		ő		Œ		œ		Ŕ		ŕ		Ŗ		ŗ		Ř		ř		Ś		ś		Ŝ		ŝ		Ş		ş
	0,0,308,321,		0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+0150,U+0151,U+0152,U+0153,		U+0154,U+0155,U+0156,U+0157,	U+0158,U+0159,U+015A,U+015B,	U+015C,U+015D,U+015E,U+015F,	
//																						Š		š		Ţ		ţ		Ť		ť		Ŧ		ŧ		Ũ		ũ		Ū		ū		Ŭ		ŭ		Ů		ů
	306,319,0,0,		0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+0160,U+0161,U+0162,U+0163,		U+0164,U+0165,U+0166,U+0167,	U+0168,U+0169,U+016A,U+016B,	U+016C,U+016D,U+016E,U+016F,		
//																						Ű		ű		Ų		ų		Ŵ		ŵ		Ŷ		ŷ		Ÿ		Ź		ź		Ż		ż		Ž		ž		ſ		
	0,0,0,0,			0,0,0,0,			323,0,0,0,			0,309,322,0,		// U+0170,U+0171,U+0172,U+0173,		U+0174,U+0175,U+0176,U+0177,	U+0178,U+0179,U+017A,U+017B,	U+017C,U+017D,U+017E,U+017F,	

// General Punctuation (656 - 767) (112 glyphs)-------------
//																						
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+2000,U+2001,U+2002,U+2003,		U+2004,U+2005,U+2006,U+2007,	U+2008,	U+2009,U+200A,U+200B,	U+200C,U+200D,U+200E,U+200F,		
//																						‐		‑		‒		–		—		―		‖		‗		‘		’		‚		‛		“		”		„		‟
	0,0,0,315,			316,0,0,0,			310,311,298,0,		312,313,300,0,		// U+2010,U+2011,U+2012,U+2013,		U+2014,U+2015,U+2016,U+2017,	U+2018,U+2019,U+201A,U+201B,	U+201C,U+201D,U+201E,U+201F,		
//																						†		‡		•		‣		․		‥		…		‧										
	302,303,314,0,		0,0,301,0,			0,0,0,0,			0,0,0,0,			// U+2020,U+2021,U+2022,U+2023,		U+2024,U+2025,U+2026,U+2027,	U+2028,U+2029,U+202A,U+202B,	U+202C,U+202D,U+202E,U+202F,		
//																						‰		‱		′		″		‴		‵		‶		‷		‸		‹		›		※		‼		‽		‾		‿
	305,0,0,0,			0,0,0,0,			0,307,320,0,		0,0,0,0,			// U+2030,U+2031,U+2032,U+2033,		U+2034,U+2035,U+2036,U+2037,	U+2038,U+2039,U+203A,U+203B,	U+203C,U+203D,U+203E,U+203F,	
//																						⁀		⁁		⁂		⁃		⁄		⁅		⁆		⁇		⁈		⁉		⁊		⁋		⁍		⁎		⁏
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+2040,U+2041,U+2042,U+2043,		U+2044,U+2045,U+2046,U+2047,	U+2048,U+2049,U+204A,U+204B,	U+204C,U+204D,U+204E,U+204F,		
//																						⁐		⁑		⁒		⁓		⁔		⁕		⁖		⁗		⁘		⁙		⁚		⁛		⁜		⁝		⁞
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+2050,U+2051,U+2052,U+2053,		U+2054,U+2055,U+2056,U+2057,	U+2058,U+2059,U+205A,U+205B,	U+205C,U+205D,U+205E,U+205F,	
//																						
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+2060,U+2061,U+2062,U+2063,		U+2064,U+2065,U+2066,U+2067,	U+2068,U+2069,U+206A,U+206B,	U+206C,U+206D,U+206E,U+206F,		


// Currency Symbols (768 - 815) (48 glyphs)-------------
//																						₠		₡		₢		₣		₤		₥		₦		₧		₨		₩		₪		₫		€		₭		₮		₯	
	0,0,0,0,			0,0,0,0,			423,0,0,0,			297,0,0,0,			// U+20A0,U+20A1,U+20A2,U+20A3,		U+20A4,U+20A5,U+20A6,U+20A7,	U+20A8,U+20A9,U+20AA,U+20AB,	U+20AC,U+20AD,U+20AE,U+20AF,	
//																						₰		₱		₲		₳		₴		₵		₶		₷		₸		₹		₺		₻		₼		₽		₾		₿	
	0,0,0,0,			0,0,0,0,			0,433,0,0,			0,0,0,0,			// U+20B0,U+20B1,U+20B2,U+20B3,		U+20B4,U+20B5,U+20B6,U+20B7,	U+20B8,U+20B9,U+20BA,U+20BB,	U+20BC,U+20BD,U+20BE,U+20BF,		
//																						
	0,0,0,0,			0,0,0,0,			0,0,0,0,			0,0,0,0,			// U+20C0,U+20C1,U+20C2,U+20C3,		U+20C4,U+20C5,U+20C6,U+20C7,	U+20C8,U+20C9,U+20CA,U+20CB,	U+20CC,	U+20CD,U+20CE,U+20CF,		
//																						Ð		Ñ		Ò		Ó		Ô		Õ		Ö		×		Ø		Ù		Ú		Û		Ü		Ý		Þ		ß	

};




#if __GNUC__ || __CYGWIN__			// gcc
#define sprintf_s snprintf
#define fprintf_s fprintf
#define memcpy_s memcpy_s
#define strcpy_s strcpy_s
#define strcat_s strcat_s
#define strerror_s strerror_s
#define _itoa_s _itoa_s
#define _strnicmp strncasecmp 
#define _stricmp strcasecmp 
#define _getch getch 

#endif


#if __GNUC__ || __CYGWIN__			// gcc
static inline char* strcpy_s(char* strDest, size_t size, const char* strSource)
{
	return strncpy(strDest, strSource, size);
}
static inline char* strcat_s(char* strDest, size_t size, const char* strSource)
{
	return strncat(strDest, strSource, size);
}
static inline void* memcpy_s(void* dest, size_t destSize, const void* src, size_t count)
{
	return memcpy(dest, src, count);
}
#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && !_GNU_SOURCE

static inline int strerror_s(char* buffer, size_t sizeInBytes, int errnum)
{
	return strerror_r(errnum, buffer, sizeInBytes);
}
#else
static inline char* strerror_s(char* buffer, size_t sizeInBytes, int errnum)
{
	//return strerror_r(errnum, buffer, sizeInBytes);			// This works but error message is not copied into buffer
	const char* ptrerr = strerror(errnum);						// use this non-thread safe function. No other go!
	strcpy_s(buffer, sizeInBytes, ptrerr);
	return buffer;
}
#endif
static inline char* _itoa_s(int value, char* buffer, size_t size, int radix)
{
	snprintf(buffer, size, "%-d", value);
	return buffer;
}
#endif


#define MAPUNICODE_H
#endif




