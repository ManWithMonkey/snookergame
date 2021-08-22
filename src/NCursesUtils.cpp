#include "NCursesUtils.hpp"

void EventCallbackClass::KeyEvent(int key){
}

void EventCallbackClass::ResizeEvent(){
}

void EventCallbackClass::MouseEvent(int x, int y, mmask_t buttonStateBits){
}

unsigned long TerminalColorModule::GetColorKey(unsigned short r, unsigned short g, unsigned short b){
	return 1E8 * r + 1E4 * g + b;
}

void TerminalColorModule::MarkColorAsUsed(unsigned long key){
	auto it = std::find_if(colorCache.begin(), colorCache.end(), [key](const Color& c){
		return key == c.colorKey;
	});

    if(it != colorCache.end())
        it->usedInLastRefresh = true;
}

TerminalColorModule::TerminalColorModule() :
    colorCache(colorCacheSize), colorsUsedCounter(0)
{
}

void TerminalColorModule::RefreshStart(){
	for(int i=0; i<colorsUsedCounter; i++){
		colorCache[i].usedInLastRefresh = false;
	}
}

void TerminalColorModule::RemoveUnused(){
	std::vector<Color> newCache(colorCacheSize);

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
    int key = GetColorKey(r, g, b);

	auto it = std::find_if(colorCache.begin(), colorCache.end(), [key](const Color& c){
		return key == c.colorKey;
	});

	if(it == colorCache.end()){
        if(colorsUsedCounter >= colorCacheSize)
            return -1;

		int newId = colorsUsedCounter + minColorIndex;

        CHECK(init_color(newId, r, g, b));
        CHECK(init_pair(newId, COLOR_BLACK, newId));
        colorCache[colorsUsedCounter].colorKey = key;
        colorCache[colorsUsedCounter].colorpair_id = newId;
        colorCache[colorsUsedCounter].usedInLastRefresh = true;

        colorsUsedCounter ++;

        return newId;
	}
    
    it->usedInLastRefresh = true;
    return it->colorpair_id;
}
