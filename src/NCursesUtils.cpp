#include "NCursesUtils.hpp"

void EventCallbackClass::KeyEvent(int key){
}

void EventCallbackClass::ResizeEvent(){
}

void EventCallbackClass::MouseEvent(int x, int y, mmask_t buttonStateBits){
}

ColorKeyStruct& ColorKeyStruct::operator=(Color color){
    colorKey = GetColorKey(color.r, color.g, color.b);
    return *this;
}

unsigned long ColorKeyStruct::GetColorKey(unsigned short r, unsigned short g, unsigned short b){
	return 1E8 * r + 1E4 * g + b;
}

void TerminalColorModule::MarkColorAsUsed(unsigned long key){
	auto it = std::find_if(colorCache.begin(), colorCache.end(), [key](const ColorKeyStruct& c){
		return key == c.colorKey;
	});

    if(it != colorCache.end())
        it->usedInLastRefresh = true;
}

TerminalColorModule::TerminalColorModule() :
    colorCache(colorCacheSize), colorsUsedCounter(0)
{
}

void TerminalColorModule::ResetColorFlags(){
	for(int i=0; i<colorsUsedCounter; i++){
		colorCache[i].usedInLastRefresh = false;
	}
}

void TerminalColorModule::RemoveUnusedColors(){
	std::vector<ColorKeyStruct> newCache(colorCacheSize);

    // shifts every used color to the left
    int i=0;
    for(int j=0; j<colorsUsedCounter; j++){
        if(colorCache[j].usedInLastRefresh){
            newCache[i++] = colorCache[j];
        }
    }
    
    colorsUsedCounter = i;
    colorCache = newCache;
}

int TerminalColorModule::GetIdOfColorPair(unsigned short r, unsigned short g, unsigned short b){
    ColorKeyStruct keystruct;
    keystruct = Color{r, g, b};

    int key = keystruct.colorKey;

	auto it = std::find_if(colorCache.begin(), colorCache.end(), [key](const ColorKeyStruct& c){
		return key == c.colorKey;
	});

    // didnt find color
	if(it == colorCache.end()){
        // no more room, return error
        if(colorsUsedCounter >= colorCacheSize)
            return -1;

		int newId = colorsUsedCounter + minColorIndex;

        CHECK(init_color(newId, r, g, b));
        CHECK(init_pair(newId, COLOR_BLACK, newId));
        colorCache[colorsUsedCounter].colorKey = key;
        colorCache[colorsUsedCounter].colorpair_id = newId;
        colorCache[colorsUsedCounter].usedInLastRefresh = true;

        colorsUsedCounter ++;

        // return newly initialized color
        return newId;
	}
    
    // return found color, set as used
    it->usedInLastRefresh = true;
    return it->colorpair_id;
}
