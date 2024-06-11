# Hurting plugin
---
this is a [conter-strike 2](https://en.wikipedia.org/wiki/Counter-Strike_2) plugin based on [swifltly](https://github.com/swiftly-solution/swiftly) that hurt you when you do something wrong in the game

## Installation
To use this plugin, you have to install swiftly. You can follow this [tutorial](https://www.youtube.com/watch?v=0NG2ew_kxrg).
Once you did it, you can get the plugin from the [action tab](https://github.com/LeBeaufort/hurting-plugin/actions). You will get a zip file containaing the plugin. Drag and drop the folder `hurting-plugin` (it is in `hurting-plugin Plugin.zip\plugins\`) in `yourcs2server\game\csgo\addons\swiftly\plugins`. You can now run the server and hurting plugin should be running.

## Configuration
You will need to configure the database for this plugin. For this, edit the file `yourcs2server\game\csgo\addons\swiftly\configs\databases.json` and add a new connection by adding this at the end of the file : 
```
"HURTINGP": {
	"hostname": "",
    "username": "",
    "password": "",
    "database": "",
    "port": 3306
},
```

You can now enjoy it !
