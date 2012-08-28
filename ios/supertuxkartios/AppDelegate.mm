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

void irrGameLoop()
{
    if (!device->isWindowActive()) {
        return;
    }
    driver->beginScene(true, true, SColor(255,100,101,140));
    
    smgr->drawAll();
    guienv->drawAll();
    driver->endScene();
    
//    if (device->isWindowActive())
//    {
//        u32 time = device->getTimer()->getTime();
//        core::rect<s32> imp1(349,15,385,78);
//        core::rect<s32> imp2(387,15,423,78);
//        
//        driver->beginScene(true, true, video::SColor(255,120,102,136));
//        
//        /*
//         First, we draw 3 sprites, using the alpha channel we
//         created with makeColorKeyTexture. The last parameter
//         specifies that the drawing method should use this alpha
//         channel. The last-but-one parameter specifies a
//         color, with which the sprite should be colored.
//         (255,255,255,255) is full white, so the sprite will
//         look like the original. The third sprite is drawn
//         with the red channel modulated based on the time.
//         */
//        
//        // draw fire & dragons background world
//        driver->draw2DImage(images, core::position2d<s32>(50,50),
//                            core::rect<s32>(0,0,342,224), 0,
//                            video::SColor(255,255,255,255), true);
//        
//        // draw flying imp
//        driver->draw2DImage(images, core::position2d<s32>(164,125),
//                            (time/500 % 2) ? imp1 : imp2, 0,
//                            video::SColor(255,255,255,255), true);
//        
//        // draw second flying imp with colorcylce
//        driver->draw2DImage(images, core::position2d<s32>(270,105),
//                            (time/500 % 2) ? imp1 : imp2, 0,
//                            video::SColor(255,(time) % 255,255,255), true);
//        
//        /*
//         Drawing text is really simple. The code should be self
//         explanatory.
//         */
//        
//        // draw some text
//        if (font)
//            font->draw(L"This demo shows that Irrlicht is also capable of drawing 2D graphics.",
//                       core::rect<s32>(130,10,300,50),
//                       video::SColor(255,255,255,255));
//        
//        // draw some other text
//        if (font2)
//            font2->draw(L"Also mixing with 3d graphics is possible.",
//                        core::rect<s32>(130,20,300,60),
//                        video::SColor(255,time % 255,time % 255,255));
//        
//        /*
//         Next, we draw the Irrlicht Engine logo (without
//         using a color or an alpha channel). Since we slightly scale
//         the image we use the prepared filter mode.
//         */
//        driver->enableMaterial2D();
//        driver->draw2DImage(images, core::rect<s32>(10,10,108,48),
//                            core::rect<s32>(354,87,442,118));
//        driver->enableMaterial2D(false);
//        
//        /*
//         Finally draw a half-transparent rect under the mouse cursor.
//         */
////        core::position2d<s32> m = device->getCursorControl()->getPosition();
////        driver->draw2DRectangle(video::SColor(100,255,255,255),
////                                core::rect<s32>(m.X-20, m.Y-20, m.X+20, m.Y+20));
//        
//        driver->endScene();
//    }
}


@implementation AppDelegate

@synthesize window = _window;
@synthesize viewController = _viewController;

- (void)dealloc
{
    if (device) {
        device->drop();
        device = NULL;
    }

    [_window release];
    [_viewController release];
    [super dealloc];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    CGRect rect = [[UIScreen mainScreen] bounds];
    _window = [[UIWindow alloc] initWithFrame:rect];

    SIrrlichtCreationParameters p;
    p.DriverType = video::EDT_OGLES1;
    p.WindowSize = dimension2d<u32>(rect.size.width, rect.size.height);
    p.Bits = 16;
    p.Fullscreen = true;
    p.Stencilbuffer = true;
    p.Vsync = true;
    p.EventReceiver = 0;
    p.WindowId = _window;

    device = createDeviceEx(p);
    
	if (!device)
		return 1;
    
	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();
    
	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                            core::rect<s32>(10,10,260,22), true);
	IAnimatedMesh* mesh = smgr->getMesh("media/sydney.md2");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture( 0, driver->getTexture("media/sydney.bmp") );
	}
	smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

    
    
    
//    images = driver->getTexture("media/2ddemo.png");
//	driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));
//    
//	/*
//     To be able to draw some text with two different fonts, we first load
//     them. Ok, we load just one. As the first font we just use the default
//     font which is built into the engine. Also, we define two rectangles
//     which specify the position of the images of the red imps (little flying
//     creatures) in the texture.
//     */
//	font = device->getGUIEnvironment()->getBuiltInFont();
//	font2 =
//    device->getGUIEnvironment()->getFont("media/fonthaettenschweiler.bmp");
//    
//	/*
//     Prepare a nicely filtering 2d render mode for special cases.
//     */
//	driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
//	driver->getMaterial2D().AntiAliasing=video::EAAM_FULL_BASIC;

    [_window makeKeyAndVisible];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
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
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
