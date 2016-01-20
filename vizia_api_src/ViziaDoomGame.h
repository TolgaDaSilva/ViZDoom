#ifndef __VIZIA_MAIN_H__
#define __VIZIA_MAIN_H__

#include "ViziaDefines.h"
#include "ViziaDoomController.h"

#include <string>
#include <vector>
#include <list>

namespace Vizia {

    unsigned int DoomTics2Ms(unsigned int tics);

    unsigned int Ms2DoomTics(unsigned int ms);

    float DoomFixedToFloat(int doomFixed);

    class DoomGame {

    public:

        struct State {
            unsigned int number;
            std::vector<int> gameVariables;
            uint8_t * imageBuffer;
        };

        DoomGame();
        virtual ~DoomGame();

        bool loadConfig(std::string filename);

        bool init();
        void close();

        void newEpisode();
        bool isRunning();

        void setAction(std::vector<int> &actions);
        void advanceAction();
        void advanceAction(bool stateUpdate, bool renderOnly, unsigned int tics);

        float makeAction(std::vector<int> &actions);
        float makeAction(std::vector<int> &actions, unsigned int tics);
        
        State getState();

        std::vector<int> getLastAction();

        bool isNewEpisode();
        bool isEpisodeFinished();

        void addAvailableButton(Button button);
        void addAvailableButton(Button button, int maxValue);
        void clearAvailableButtons();
        int getAvailableButtonsSize();
        void setButtonMaxValue(Button button, int maxValue);
        int getButtonMaxValue(Button button);

        void addAvailableGameVariable(GameVariable var);

        void clearAvailableGameVariables();
        int getAvailableGameVariablesSize();

        void addCustomGameArg(std::string arg);
        void clearCustomGameArgs();

        void sendGameCommand(std::string cmd);

        uint8_t * const getGameScreen();

        Mode getMode();
        void setMode(Mode mode);

        //OPTIONS

        int getGameVariable(GameVariable var);

        float getLivingReward();
        void setLivingReward(float livingReward);
        float getDeathPenalty();
        void setDeathPenalty(float deathPenalty);

        float getLastReward();
        float getSummaryReward();

        void setDoomGamePath(std::string path);
        void setDoomIwadPath(std::string path);
        void setDoomFilePath(std::string path);
        void setDoomMap(std::string map);
        void setDoomSkill(int skill);
        void setDoomConfigPath(std::string path);

        unsigned int getSeed();
        void setSeed(unsigned int seed);

        void setAutoNewEpisode(bool set);
        void setNewEpisodeOnTimeout(bool set);
        void setNewEpisodeOnPlayerDeath(bool set);
        void setNewEpisodeOnMapEnd(bool set);

        unsigned int getEpisodeStartTime();
        void setEpisodeStartTime(unsigned int tics);

        unsigned int getEpisodeTimeout();
        void setEpisodeTimeout(unsigned int tics);

        unsigned int getEpisodeTime();

        void setScreenResolution(ScreenResolution resolution);
        void setScreenFormat(ScreenFormat format);
        void setRenderHud(bool hud);
        void setRenderWeapon(bool weapon);
        void setRenderCrosshair(bool crosshair);
        void setRenderDecals(bool decals);
        void setRenderParticles(bool particles);
        void setWindowVisible(bool visibility);
        void setConsoleEnabled(bool console);

        int getScreenWidth();
        int getScreenHeight();
        int getScreenChannels();
        size_t getScreenPitch();
        size_t getScreenSize();

        ScreenFormat getScreenFormat();

    protected:

        DoomController *doomController;
        bool running;

        /* STATE AND ACTIONS */
        Mode mode;

        State state;
        void updateState();

        std::vector <GameVariable> availableGameVariables;
        std::vector <Button> availableButtons;

        std::vector<int> lastAction;

        /* Reward */
        unsigned int nextStateNumber;
        unsigned int lastMapTic;

        float lastReward;
        float lastMapReward;
        float summaryReward;

        float livingReward;
        float deathPenalty;

    private:
        /* Load config helpers */
        static bool StringToBool(std::string boolString);
        static ScreenResolution StringToResolution(std::string str);
        static ScreenFormat StringToFormat(std::string str);
        static Button StringToButton(std::string str);
        static GameVariable StringToGameVariable(std::string str);
        static unsigned int StringToUint(std::string str);
        static bool ParseListProperty(int& line_number, std::string& value, std::ifstream& input, std::vector<std::string>& output);
    

        //HELPERS
        bool checkFilePath(std::string path);

        void logError(std::string error);

        void logWarning(std::string warning);

        void log(std::string log);
    };
}

#endif
