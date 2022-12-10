# UTF8Map
----------------------------------------------------------------------------------------
##### _UTF-8 Support for t42 font (Type 0 composite font with CIDFontType 2) from a Demo Program  written in C++._ 

##### Linux Platform.
----------------------------------------------------------------------------------------
##### Description
This standalone utility, written in C++, utilizes `t42` font (Type 0 Composite font with CIDFontType 2 and Type 42 base font) in order to generate `Hexadecimal` strings from `UTF-8` encoded strings required by Postscript's `show` operator. Bear in mind that the `t42` has been converted from a TrueType font. You need this conversion because without this conversion, a postscript program can't access a truetype font!

The CIDMap of `t42` font enforces an identity mapping as follows:
```
Character code 0 maps to Glyph index 0
Character code 1 maps to Glyph index 1
Character code 2 maps to Glyph index 2
......
Character code NumGlyphs-1 maps to Glyph index NumGlyphs-1
```
It is clearly evident that there is no unicode involved in this mapping. To understand concretely, edit the following postscript program `tamil.ps` that accesses `t42` font through postscript's `findfont` operator.

```
%!PS-Adobe-3.0
/myNoTo {/NotoSansTamil-Regular findfont exch scalefont setfont} bind def
13 myNoTo
100 600 moveto 
% தமிழ் தங்களை வரவேற்கிறது!
<0019001d002a005e00030019004e00120030002200030024001f002f0024005b0012002a0020007a00aa> show
100 550 moveto 
% Tamil Welcomes You!
<0155017201aa019801a500030163018801a5017f01b101aa018801c20003016901b101cb00aa00b5> show
showpage
```
Issue the following Ghostscript command  to execute the postscript program `tamil.ps`. 
- `gs ~/cidfonts/NotoSansTamil-Regular.t42 ~/cidfonts/tamil.ps`

This will display two strings `தமிழ் தங்களை வரவேற்கிறது!` and `Tamil Welcomes You!`.

Note that the strings for `show` operator are in Hexadecimal format embedded within angular brackets. Operator `show` extracts 2 bytes at a time and maps this CID (16 bit value) to a Glyph. For example, the first 4 Hex digits in the 1st string is `0019` whose decimal equivalent is `25`. This maps to glyph `த`.

In order to use this font `t42`, each string (created from character set of a `ttf`) should be converted into hexadecimal string by hand which is practically impossible and therefore this font becomes futile.

Now consider the following C++ code that generates a postscript program called `myNotoTamil.ps` that accesses `t42` font through postscript's `findfont` operator.

```
const short lcCharCodeBufSize = 200;	// Character Code buffer size.
char bufCharCode[lcCharCodeBufSize];	// Character Code buffer
FILE *fps = fopen ("~/cidfonts/myNotoTamil.ps", "w");

fprintf (fps, "%%!PS-Adobe-3.0\n");
fprintf (fps, "/myNoTo {/NotoSansTamil-Regular findfont exch scalefont setfont} bind def\n");
fprintf (fps, "13 myNoTo\n");
fprintf (fps, "100 600 moveto\n");
fprintf (fps, u8"%% தமிழ் தங்களை வரவேற்கிறது!\n");
fprintf (fps, "<%s> show\n", strps(ELang::eTamil, EMyFont::eNoToSansTamil_Regular, u8"தமிழ் தங்களை வரவேற்கிறது!", bufCharCode, lcCharCodeBufSize));
fprintf (fps, "%% Tamil Welcomes You!\n");
fprintf (fps, "<%s> show\n", strps(ELang::eTamil, EMyFont::eNoToSansTamil_Regular, u8"Tamil Welcomes You!", bufCharCode, lcCharCodeBufSize));
fprintf (fps, "showpage\n");
fclose (fps);
```

Although the contents of `tamil.ps` and `myNotoTamil.ps` are same and identical, the difference in the production of those `ps` files is like difference between heaven and earth!
Observe that unlike `tamil.ps`(handmade Hexadecimal strings), the `myNotoTamil.ps` is generated by a C++ program uses UTF-8 encoded strings directly hiding the hex strings completely. The function  **strps** produces hex strings from UTF-8 encoded strings which are the same and identical as the strings present in `tamil.ps`. The futile `t42` font has suddenly become fruitful due to **strps** function's mapping ability from UTF-8 to CIDs (every 2 bytes in Hex strings maps to a CID)!

##### What is UTF-8 encoding?

It is mandatory to understand UTF-8 encoding before exploring **strps** function. UTF-8 encoding is a variable sized encoding scheme to represent unicode code points in memory. Variable sized encoding means the code points are represented using 1, 2, 3, 4, 5 or 6 bytes depending on their size. They are explained below:
1. `UTF-8 1 byte encoding:` A 1 byte encoding is identified by the presence of **0** in the first bit (**0**xxxxxxx). i.e code points in the ASCII range 0 to 127  are represented by a single byte.
2. `UTF-8 2 byte encoding:` 2 byte encoding is identified by the presence of the bit sequence **110** in the first byte and **10** in the second byte (**110**xxxxx **10**xxxxxx) respectively. i.e. code points in the range (128-2047) are represented by two bytes.
3. `UTF-8 3 byte encoding:` A 3 byte encoding is identified by the presence of the bit sequence **1110** in the first byte and **10** in the second and third bytes (**1110**xxxx **10**xxxxxx **10**xxxxxx) respectively. i.e. code points in the range (2048-65535) are represented by three bytes.
4. `UTF-8 4 byte encoding:` A 4 byte encoding is identified by the presence of the bit sequence **11110** in the first byte and **10** in the second, third and fourth bytes (**11110**xxx **10**xxxxxx **10**xxxxxx **10**xxxxxx) respectively. i.e. code points in the range (65536-2097151) are represented by four bytes.
5. `UTF-8 5 byte encoding:` A 5 byte encoding is identified by the presence of the bit sequence **111110** in the first byte and **10** in the second, third, fourth and fifth bytes (**111110**xx **10**xxxxxx **10**xxxxxx **10**xxxxxx **10**xxxxxx) respectively. i.e. code points in the range (2097152-67108863) are represented by five bytes. 
6. `UTF-8 6 byte encoding:` A 6 byte encoding is identified by the presence of the bit sequence **1111110** in the first byte and **10** in the second, third, fourth, fifth and sixth bytes (**1111110**x **10**xxxxxx **10**xxxxxx **10**xxxxxx **10**xxxxxx **10**xxxxxx) respectively. i.e. code points in the range (67108864-2147483647) are represented by six bytes. 

##### What is strps function?
This is a mapping function that produces CIDs from UTF-8 encoded strings by performing the following tasks:
1. Decodes UTF-8 encoded string and collects atmost four Unicode Points into `quad` buffer. This buffer won't hold more than 4 unicode points any time.
2. Dispatches quad buffer (consisting of atmost 4 Unicode Points) to function **up2cid** which maps `Unicode Points` to CIDs with the help of a `mapping table` (implemented as a single dimensional array constructed with the help of Unicode Blocks. Refer `mapunicode.h`).
   - The first parameter of **up2cid** function is language code `pLan` which is one of Tamil, Hindi, Malayalam, Telugu, Kannada, Marathi, Gujarati,odia, Punjabi, Bengali, Assamese. Refer `mapunicode.h`.
   - The second parameter of **up2cid** function is `pFont` of type EFont. There are as many as 10 fonts are supported for each language. Refer `aFont` which is a two-dimensional array of structure `SFont` in `mapunicode.h`.
   - The third parameter of **up2cid** function is `pUnicodeQuad` which is a `quad` array of type uint32_t. This will contain atmost 4 Unicode Points. The number of unicode points present in the quad array is indicated by the 4th paramater `pCntUnicode`. This varies from 1 to 4. Bear in mind that this number will never exceed 4.
   - The fourth parameter of **up2cid** function is `pCntUnicode` which is a reference variable of type short. The caller sets this to the number of Unicode Points present in the `quad` array (3rd parameter). Up on returning, `pCntUnicode` passes out the **untouced** number of Unicode Points present in the `quad` array which will be recycled subsequently by the caller (**strps** function). A value of zero indicates that all the Unicode Points present in the `quad` array have been consumed by **up2cid** function.
   - The fifth and final parameter of **up2cid** function is `pCID` which is a ternary array of type short. This is an output array that passes out atmost 3 CIDs corresponding to Unicode Points present in the `quad` array (3rd parameter). This requires more explanation with the help of the following 6 cases representing the workings of entire **up2cid** function.
      - The glyph `ஸ்ரீ` consists of `ஸ +  ் + ர + ீ` which corresponds to four Unicode Points U+0BB8, U+0BCD, U+0BB0 and U+0BC0 respectively. The CID for glyph `ஸ்ரீ` is 163 and Unicode Points consumed by this glyph are four. Since all Unicode points in `quad` array are consumed, `pCntUnicode` passes out zero to the caller who will understand that it will have to refill quad array with atmost four Unicode Points from UTF-8 encoded input string. The ternary array is filled with only one CID and the return value of function **up2cid** will be 1 (Number of CIDs present in the ternary array `pCID`).
      - The glyph `க்ஷொ` consists of `க + ் + ஷ + ௌ` which corresponds to four Unicode Points U+0B95, U+0BCD, U+0BB7 and U+0BCA respectively. The `க + ் + ஷ + ௌ` is same and identical to `ெ + க + ் + ஷ + ா` whose Unicode Points are U+0BC6, U+0B95, U+0BCD, U+0BB7 and U+0BBE. This can be further reduced to `ெ + க + க்ஷ + ா`  whose Unicode Points are U+0BC6, U+0B95, none, and U+0BBE. The CIDs for glyph `க்ஷொ` are 46, 76 and 41. The Unicode Points consumed by this glyph are four. Since all Unicode points in `quad` array are consumed, `pCntUnicode` passes out zero to the caller who will understand that it will have to refill `quad` array with atmost four Unicode Points from UTF-8 encoded input string. The ternary array is filled with three CIDs and the return value of function **up2cid** will be 3 (Number of CIDs present in the ternary array).
      - The glyph `க்ஷ` consists of `க + ் + ஷ` which corresponds to three Unicode Points U+0B95, U+0BCD and U+0BB7 respectively. The CID for glyph `க்ஷ` is 76 and Unicode Points consumed by this glyph are three. The untouched Unicode points in quad array is 1 which is passed out by `pCntUnicode` to the caller who will understand that there is only one Unicode Point to recyle and append `quad` array with atmost three Unicode Points from UTF-8 encoded input string. The ternary array is filled with only one CID and the return value of function **up2cid** will be 1 (Number of CIDs present in the ternary array). 
      - The glyph `மா` consists of `ம + ா` which corresponds to two Unicode Points U+0BAE and U+0BBE respectively. The CIDs for glyph `மா`  are 29 and 41. The Unicode Points consumed by this glyph are two. The untouched Unicode points in `quad` array is 2 which is passed out by `pCntUnicode` to the caller who will understand that there are two Unicode Point to recyle and append `quad` array with atmost two Unicode Points from UTF-8 encoded input string. The ternary array is filled with both CIDs and the return value of function **up2cid** will be 2 (Number of CIDs present in the ternary array which will never exceed 3).
      - The glyph `லோ` consists of `ல + ோ` which corresponds to two Unicode Points U+0BB2 and U+0BCB respectively. The `ல + ோ` is same and identical to `ே + ல + ா` whose Unicode Points are U+0BC7, U+0BB2 and U+0BBE. The CIDs for glyph `லோ`  are 47, 33 and 41. The Unicode Points consumed are 2. The untouched Unicode points in Quad array is 2 which is passed out by pCntUnicode to the caller who will understand that there are two Unicode Point to recyle and append `quad` array with atmost two Unicode Points from UTF-8 encoded input string. The ternary array is filled with 3 CIDs and the return value of function up2cid will be 3 (Number of CIDs present in the ternary array which will never exceed 3).
      - The glyph `ஔ` is a vowel whose Unicode Point is U+0B94. The CID for glyph `ஔ`  is 17 and Unicode Points consumed is only one. The untouched Unicode points in `quad` array are 3 which are passed out by `pCntUnicode` to the caller who will understand that there are three Unicode Point to recyle and append `quad` array with atmost one Unicode Point from UTF-8 encoded input string. The ternary array is filled with only one CID and the return value of function **up2cid** will be 1 (Number of CIDs present in the ternary array).
3. Post Processing after return from function **up2cid** is an important task. Based on the return value from **up2cid** function, **strps** knows how many CIDs are present in the ternary array `pCID` and copies the CIDs into 3rd parameter `pPSOutString` (an array of characters) in hex format which will be passed subsequently to Postscript's `show` operator. Variable `cntUnicode` indicates how many Unicode Points are consumed. The untouched Unicode Points (if any) will be recycled by **strps** function and empty slots of quad array will be filled with Unicode points by the program logic.  A value of zero means an empty `quad` array which will be refilled with atmost 4 Unicode points decoded from UTF-8 string. This process repeats until  parameter `pUTF8InString` which holds UTF-8 encoded string is exhausted completely.
         
 ##### struct SMyFont
The `typedef` of C++ structure is given below that helps in choosing a font. Refer `mapunicode.h`.
```
typedef struct SMyFont {
	short numGlyphs;		// total glyphs in the character set.
	const char *name;		// font name such as 'myNotoTamil' and 'myLathaTamil'
	const char *psname;		// Postscript font name such as 'NotoSansTamil-Regular'
	const char *fname;		// File name of the font such as 'NotoSansTamil-Regular.t42'
} SMyFont;
```

##### static const SMyFont asMyFont[cMaxLanguage + 1][10+2].
This two-dimensional array of type `struct SMyFont` is declared and initialized in `mapunicode.h`. Each language is allotted a slot. There are 12 sub-slots are present within main slot and supports maximum 10 fonts per language. The first and last sub-slots are filled with zero entries. At present sub-slots for Language `Tamil` has 4 entries and for other languages they are left empty as shown below:
```
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

	...so on...
```

##### struct SUnicodeBlock
 `typedef` of C++ structure is given below that supplies Unicode Block range of `begin` and `end` for each language supported. Refer `mapunicode.h`.
```
typedef struct SUnicodeBlock {
	ELang lan;									// Language supported by MY Software.
	uint32_t blockBeg;							// Beginning of Unicode Block corresponding to the laguage.
	uint32_t blockEnd;							// Beginning of Unicode Block corresponding to the laguage.
} SUnicodeBlock;
```

##### static const SUnicodeBlock aUnicode[cMaxLanguage + 1].
This single-dimensional array of type `struct SUnicodeBlock` is declared and initialized in `mapunicode.h`. Each language is allotted a slot. The entires are shown below:
```
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
```


##### Mapping tables aNotoSansTamilMap and aLathaTamilMap.
These tables are implemented as single-dimensional array of type short (refer `mapunicode.h`). The entries in these mapping tables are divided logically into 7 sections based on Unicode Blocks except one as follows:

1. Based on Unicode Block for `Tamil` (U+0B80 to U+0BFF), there are 128 entries. The offset of this section is `zero` w.r.t. the beginning of mapping table.
2. This is the only section which is not associated with any Code Block and this section belongs to Tamil Glyphs with no Unicode Points. There are 144 entries and the offset is `128` w.r.t. the beginning of mapping table.
3. This section belongs to `Basic Latin` whose Unicode Block is from U+0000 to U+007F. There are 128 entries and the offset is `272` w.r.t. the beginning of mapping table.
4. `Latin-1 Supplement` is associated with this section having Unicode Block is from U+0080 to U+00FF. There are 128 entries and the offset is `400` w.r.t. the beginning of mapping table.
5. This section belongs to `Latin Extended-A` whose Unicode Block is from U+0100 to U+017F. There are 128 entries and the offset is `528` w.r.t. the beginning of mapping table.
6. This section is for `General Punctuation` whose Unicode Block is from U+2000 to U+206F. There are 112 entries and the offset is `656` w.r.t. the beginning of mapping table.
7. This section belongs to `Currency Symbols` whose Unicode Block is from U+20A0 to U+20CF. There are 48 entries and the offset is `768` w.r.t. the beginning of mapping table.

Total number of entries in the table (single-dimensional array) is `128 + 144 + 128 + 128 + 128 + 112 + 48' = **816**.

##### How does the function 'up2cid' find out the CID corresponding to a Unicode Point?
The function **up2cid** adopts the following procedure to determine the CID from Unicode Point. This function inspects the zeroth slot of quad array `pUnicodeQuad` that contains unicode points as follows:
1. Does Unicode Point of zeroth slot fall in `Basic Latin` Unicode Block (U+0000 - U+00FF)? If so, then `addr = pUnicodeQuad[0] - aUnicode[(int)ELang::eEng].blockBeg + 272`; where `272` is offset of `Basic Latin` section w.r.t. beginning of mapping table. Location `addr` supplies Character Code(16 bits) corresponding to Unicode Point.
2. Does Unicode Point of zeroth slot fall in `Latin-1 Supplement` Unicode Block (U+0080 - U+00FF)? If so, then `addr = pUnicodeQuad[0] - 0x0080 + 400`; where `400` is offset of `Latin-1 Supplement` section w.r.t. beginning of mapping table. Location `addr` supplies Character Code(16 bits) corresponding to Unicode Point.
3. Does Unicode Point of zeroth slot fall in `Latin Extended-A` Unicode Block (U+0100 - U+017F)? If so, then `addr = pUnicodeQuad[0] - 0x0100 + 528`; where `528` is offset of `Latin Extended-A` section w.r.t. beginning of mapping table. Location `addr` supplies Character Code(16 bits) corresponding to Unicode Point.
4. Does Unicode Point of zeroth slot fall in `General Punctuation` Unicode Block (U+2000 - U+206F)? If so, then `addr = pUnicodeQuad[0] - 0x2000 + 656`; where `656` is offset of `General Punctuation` section w.r.t. beginning of mapping table. Location `addr` supplies Character Code(16 bits) corresponding to Unicode Point.
5. Does Unicode Point of zeroth slot fall in `Currency Symbols` Unicode Block (U+20A0 - U+20CF)? If so, then `addr = pUnicodeQuad[0] - 0x20A0 + 768`; where `768` is offset of `General Punctuation` section w.r.t. beginning of mapping table. Location `addr` supplies Character Code(16 bits) corresponding to Unicode Point.
6. Verify consequent 3 Unicode points maps to glyph `க்ஷ` which equals to`க + ் + ஷ` . i.e const bool isக்ஷ = pCntUnicode > 2 && pUnicodeQuad[0] == 0x0B95 && pUnicodeQuad[1] == 0x0BCD && pUnicodeQuad[2] == 0x0BB7; Since this process is lengthy refer `main.cpp` and see the code.
7. Verify consequent 4 Unicode points maps to glyph `ஸ்ரீ` which equals to`ஸ +  ்  + ர + ீ` . i.e const bool isஸ்ரீ = pCntUnicode == 4 && pUnicodeQuad[0] == 0x0BB8 && pUnicodeQuad[1] == 0x0BCD && pUnicodeQuad[2] == 0x0BB0 && pUnicodeQuad[3] == 0x0BC0; Refer `main.cpp` and see the code.
8. Next is consonants (க ங ச ஞ ட ண த ந ன ப ம ய ர ற ல ள ழ வ ஶ ஜ ஷ ஸ ஹ க்ஷ) ending with vowel sound which are ், ா, ி, ீ, ு , ூ, ெ, ே,  ை, ொ, ோ and ௌ.  Refer `main.cpp` and see the code.
9. Finally Unicode Point of slot zero of quad array maps to a Vowel. Refer `main.cpp` and see the code.
 
##### Technical Features
- This utility is a console application developed on Microsoft Visual Studio Community 2022 (64-bit) Edition- Version 17.4.2 under Windows 10.
- Note that this program is 100% portable across Windows and Linux. i.e. The source files (`main.ccp` and `mapunicode.h`) are same and identical across platforms.
- In order to build this utility in Linux, the two source files (`main.cpp` and `mapunicode.h`) were copied to  `Ubuntu` Linux platform  and `dos2unix` was invoked to replace `CR+LF` with `LF`. A `makefile` has been added up that builds the binary. A separate `README.md` was written and added in the folder. All four files have been checked into GitHub.
- Ubuntu version is 20.04.5 LTS and Ghostsciprt version is 9.5. 
- However, this utility can be built and executable on any flavor of Linux.

##### Usage
Create a folder ~/cidfonts and store `NotoSansTamil-Regular.t42` and `latha.t42`. Now issue the following commands:
- `./utf8map ~/cidfonts/NotoSansTamil-Regular.t42`
This command generates a postscript program `myNotoTamil.ps`. 
- `./utf8map ~/cidfonts/latha.t42`
This command generates a postscript program `myLathaTamil.ps`. 

Invoke Ghostscript to execute postscript program `myNotoTamil.ps` as follows:
    - `gs ~/cidfonts/NotoSansTamil-Regular.t42 ~/cidfonts/myNotoTamil.ps`

Ghostscript displays the following output in a single page:
- A welcome message in Tamil and English.
- List of Vowels (12 Glyphs). All of them are associated with Unicode Points.
- List of Consonants (18 + 6 = 24 Glyphs). No Unicode Points.
- List of combined glyphs (Combination of Vowels + Consonants) in 24 lines. Each line displays 12 glyphs. Out of 288 Glyphs, 24 are associated with Unicode Points and rest do not.
- List of Numbers in two lines. All 13 Glyphs for Tamil numbers are associated with Unicode Points.
- A foot Note.

The above display helps to corroborate all the glyhps present in Tamil language. This does not include Latin and other glyphs found in the character set of `ttf` font.

Now invoke Ghostscript to execute postscript program `myLathaTamil.ps` as follows:
    - `gs ~/cidfonts/latha.t42 ~/cidfonts/myLathaTamil.ps`

Except shape of glyphs, Ghostscript displays output similar to the output for `myNotoTamil.ps`.

##### Conversion from truetype font to CID-Keyed Font.
In order to convert a truetype font (`ttf`) to a CID-Keyed font (`t42`) a conversion utility is required. Refer [Conversion from ttf to type 2 CID font (type 42 base font)](https://stackoverflow.com/questions/73931912/conversion-from-ttf-to-type-2-cid-font-type-42-base-font/74093991#74093991).
