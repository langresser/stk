//
//  AppDelegate.m
//  ios
//
//  Created by 王 佳 on 12-8-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"

#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

IrrlichtDevice * device = NULL;
IVideoDriver* driver = NULL;
ISceneManager* smgr = NULL;
IGUIEnvironment* guienv = NULL;


video::ITexture* images;
gui::IGUIFont* font;
gui::IGUIFont* font2;

extern void onGameLoop();
extern void initGame(int w, int h, void* winid);
extern void onGameExit();

void irrGameLoop()
{
    onGameLoop();
}


@implementation AppDelegate

@synthesize window = _window;
@synthesize viewController = _viewController;

- (void)dealloc
{
    onGameExit();

    [_window release];
    [_viewController release];
    [super dealloc];
}

-(void)initGame
{
    initGame(1024, 768, _viewController);
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    CGRect rect = [[UIScreen mainScreen] bounds];
    _window = [[UIWindow alloc] initWithFrame:rect];
    _viewController = [[ViewController alloc]initWithNibName:nil bundle:nil];
    _viewController.view = [[UIView alloc]initWithFrame:rect];
    _window.rootViewController = _viewController;
    
    [self performSelector:@selector(initGame)];

    [_window makeKeyAndVisible];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    device->setWindowActive(false);
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    device->setWindowActive(true);
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
}

- (void)applicationWillTerminate:(UIApplication *)application
{
}

@end
