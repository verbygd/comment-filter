#include <Geode/modify/InfoLayer.hpp>
#include <Geode/utils/general.hpp>
#include <algorithm>
#include <vector>
#include <string>

using namespace geode::prelude;

class $modify(InfoLayer) {

    void uploadComment(gd::string commentText) {
        
        std::string text = commentText;
        std::transform(text.begin(), text.end(), text.begin(), ::tolower);

        std::vector<std::string> bannedPhrases = {
            "kill yourself", "hope you die", "kys", "death threat", "kill u", "die in a",
            "fuck", "shit", "bitch", "asshole", "dick", "cunt", "bastard", "motherfucker",
            "nsfw", "hentai", "porn", "sex", "slut", "whore", "dumbass", "jackass", "pussy"
        };

        bool foundOffensiveText = false;
        for (const auto& phrase : bannedPhrases) {
            if (text.find(phrase) != std::string::npos) {
                foundOffensiveText = true;
                break;
            }
        }

        if (foundOffensiveText) {
            auto alert = FLAlertLayer::create(
                "Warning!", 
                "Hey, I noticed you tried commenting something offensive. <cr>Are you sure you would like to send this message?</c> You could be banned if you aren't careful.", 
                "Cancel", 
                "Send Anyway"
            );
            alert->show();
            return;
        }

        InfoLayer::uploadComment(commentText);
    }
};
