# Endless Runner

This game is made in Unreal Engine 5.1.1. It's C++ only with close to 0 blueprint code.

## Player Controls
- **Space** | Jump
- **A key** | Move left
- **D key** | Move right

# Part 1

This part consists of only the base game. I started with the [GameMode](https://github.com/KristofferSaxmo/EndlessRunner/blob/main/Source/EndlessRunner/EndlessRunnerGameModeBase.cpp), which takes care of spawning and handling the [Platforms](https://github.com/KristofferSaxmo/EndlessRunner/blob/main/Source/EndlessRunner/Private/MyPlatform.cpp). Since the platforms will scroll by one by one and always in the same order, I ended up holding them in a **Queue**. That way I can take a platform out and put it back in the start of the queue once it has moved past the player. When requeuing them, I call MyPlatform->DeleteObstacles() to remove all of the attached obstacles. When I put them back I call MyPlatform->SpawnObstacles() again. The GameMode will also increase the velocity of all platforms and the score by the current velocity each second. If the score is a highscore, it will be saved in a .txt file once the player dies.

# Part 2

This part is a lot more fleshed out. For starters, I generalized the code so that the game can have any amount of lanes as long as it's an odd number. I made the presets 3, 5 and 7 lanes in the main menu. I set up a GameInstance to carry information about the amount of lanes and if it's multiplayer or not from the MenuLevel to the GameLevel.

Part 2 also includes an AI Co-op mode. The AI is an [AIController](https://github.com/KristofferSaxmo/EndlessRunner/blob/main/Source/EndlessRunner/Private/Player2AIController.cpp) that proccesses the oncomming platforms lanes and sets a it's desired position the the closest empty lane. It will then move towards the desired lane at a fixed pace. If the desired lane is far away, it will also jump to decrease chances getting hit.

I also made it so that every time one of the players pass an obstacle, there is a small chance that obstacles further ahead gets destroyed. It works for each player, so playing with the AI makes it easier because more obstacles are destroyed.

# Challenges

My main challenge this project has been the player input. It took a long time for me to figure out setting up the Enhanced Input System in C++. It's also the reason why I made an AI instead of player2, I just couldn't get 2 PlayerControllers to recieve input from 1 keyboard the way I wanted to.

Another challenge was setting up the platforms so that they could be easily readable for the AI. I ended up making each platform store the lanes which were clear of obstacles, and also point towards the next platform. That way I could always check the current platform and see which lanes were free to find the desired position to move to.
