# Warning

This repository is now deprecated. People looking for an updated SendProxy extension should look for [jensewe's fork](https://github.com/jensewe/Left4SendProxy). 

# Left4SendProxy

TheByKotik's SendProxy, which is a fork of Afronanny's SendProxy Manager [extension](https://forums.alliedmods.net/showthread.php?t=169795). This repository provides binaries for Left 4 Dead 2 through Github Actions.

## Repository Goals
- Provide up-to-date binaries of SendProxy to server operators, using GitHub actions.
- Provide signatures of SendProxy for Left 4 Dead 2
  - Original repository included signatures for Team Fortress 2, but as years of updates arrived to the game, and the fact I do not have a Team Fortress 2 server it makes me unable to check if they're functional.
  - Users can freely provide support for the game they want by doing a pull request.

## Changelog from the original SendProxy

- Fixed some errors
- Now SendProxy hooks calls for each client individually
- Removed std::string usage to prevent libstdc++ linking in linux build
- Added interface for extensions and some missed natives
- Removed the broken auto-updater.
- Added AMBuild scripts.
- Added GameRules hook.
