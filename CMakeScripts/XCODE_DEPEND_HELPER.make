# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# For each target create a dummy rule so the target does not have to exist
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/Debug/libbulletdynamics.a:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/Debug/libbulletcollision.a:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/Debug/libbulletmath.a:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/enet/Debug/libenet.a:
/usr/lib/libcurl.dylib:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/MinSizeRel/libbulletdynamics.a:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/MinSizeRel/libbulletcollision.a:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/MinSizeRel/libbulletmath.a:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/enet/MinSizeRel/libenet.a:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/RelWithDebInfo/libbulletdynamics.a:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/RelWithDebInfo/libbulletcollision.a:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/RelWithDebInfo/libbulletmath.a:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/enet/RelWithDebInfo/libenet.a:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/Release/libbulletdynamics.a:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/Release/libbulletcollision.a:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/Release/libbulletmath.a:
/Users/wangjiatc/Documents/MyProj/supertuxkart/src/enet/Release/libenet.a:


# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.supertuxkart.Debug:
PostBuild.bulletdynamics.Debug: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/Debug/supertuxkart.app/Contents/MacOS/supertuxkart
PostBuild.bulletcollision.Debug: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/Debug/supertuxkart.app/Contents/MacOS/supertuxkart
PostBuild.bulletmath.Debug: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/Debug/supertuxkart.app/Contents/MacOS/supertuxkart
PostBuild.enet.Debug: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/Debug/supertuxkart.app/Contents/MacOS/supertuxkart
/Users/wangjiatc/Documents/MyProj/supertuxkart/bin/Debug/supertuxkart.app/Contents/MacOS/supertuxkart:\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/Debug/libbulletdynamics.a\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/Debug/libbulletcollision.a\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/Debug/libbulletmath.a\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/enet/Debug/libenet.a\
	/usr/lib/libcurl.dylib
	/bin/rm -f /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/Debug/supertuxkart.app/Contents/MacOS/supertuxkart


PostBuild.bulletcollision.Debug:
PostBuild.bulletdynamics.Debug:
PostBuild.bulletmath.Debug:
PostBuild.enet.Debug:
PostBuild.supertuxkart.Release:
PostBuild.bulletdynamics.Release: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/Release/supertuxkart.app/Contents/MacOS/supertuxkart
PostBuild.bulletcollision.Release: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/Release/supertuxkart.app/Contents/MacOS/supertuxkart
PostBuild.bulletmath.Release: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/Release/supertuxkart.app/Contents/MacOS/supertuxkart
PostBuild.enet.Release: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/Release/supertuxkart.app/Contents/MacOS/supertuxkart
/Users/wangjiatc/Documents/MyProj/supertuxkart/bin/Release/supertuxkart.app/Contents/MacOS/supertuxkart:\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/Release/libbulletdynamics.a\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/Release/libbulletcollision.a\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/Release/libbulletmath.a\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/enet/Release/libenet.a\
	/usr/lib/libcurl.dylib
	/bin/rm -f /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/Release/supertuxkart.app/Contents/MacOS/supertuxkart


PostBuild.bulletcollision.Release:
PostBuild.bulletdynamics.Release:
PostBuild.bulletmath.Release:
PostBuild.enet.Release:
PostBuild.supertuxkart.MinSizeRel:
PostBuild.bulletdynamics.MinSizeRel: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/MinSizeRel/supertuxkart.app/Contents/MacOS/supertuxkart
PostBuild.bulletcollision.MinSizeRel: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/MinSizeRel/supertuxkart.app/Contents/MacOS/supertuxkart
PostBuild.bulletmath.MinSizeRel: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/MinSizeRel/supertuxkart.app/Contents/MacOS/supertuxkart
PostBuild.enet.MinSizeRel: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/MinSizeRel/supertuxkart.app/Contents/MacOS/supertuxkart
/Users/wangjiatc/Documents/MyProj/supertuxkart/bin/MinSizeRel/supertuxkart.app/Contents/MacOS/supertuxkart:\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/MinSizeRel/libbulletdynamics.a\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/MinSizeRel/libbulletcollision.a\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/MinSizeRel/libbulletmath.a\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/enet/MinSizeRel/libenet.a\
	/usr/lib/libcurl.dylib
	/bin/rm -f /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/MinSizeRel/supertuxkart.app/Contents/MacOS/supertuxkart


PostBuild.bulletcollision.MinSizeRel:
PostBuild.bulletdynamics.MinSizeRel:
PostBuild.bulletmath.MinSizeRel:
PostBuild.enet.MinSizeRel:
PostBuild.supertuxkart.RelWithDebInfo:
PostBuild.bulletdynamics.RelWithDebInfo: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/RelWithDebInfo/supertuxkart.app/Contents/MacOS/supertuxkart
PostBuild.bulletcollision.RelWithDebInfo: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/RelWithDebInfo/supertuxkart.app/Contents/MacOS/supertuxkart
PostBuild.bulletmath.RelWithDebInfo: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/RelWithDebInfo/supertuxkart.app/Contents/MacOS/supertuxkart
PostBuild.enet.RelWithDebInfo: /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/RelWithDebInfo/supertuxkart.app/Contents/MacOS/supertuxkart
/Users/wangjiatc/Documents/MyProj/supertuxkart/bin/RelWithDebInfo/supertuxkart.app/Contents/MacOS/supertuxkart:\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/RelWithDebInfo/libbulletdynamics.a\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/RelWithDebInfo/libbulletcollision.a\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/bullet/RelWithDebInfo/libbulletmath.a\
	/Users/wangjiatc/Documents/MyProj/supertuxkart/src/enet/RelWithDebInfo/libenet.a\
	/usr/lib/libcurl.dylib
	/bin/rm -f /Users/wangjiatc/Documents/MyProj/supertuxkart/bin/RelWithDebInfo/supertuxkart.app/Contents/MacOS/supertuxkart


PostBuild.bulletcollision.RelWithDebInfo:
PostBuild.bulletdynamics.RelWithDebInfo:
PostBuild.bulletmath.RelWithDebInfo:
PostBuild.enet.RelWithDebInfo:
