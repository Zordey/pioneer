<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

//
// Objective-C cocoa wrapper for pioneer

#import <Cocoa/Cocoa.h>

@interface SDLMain : NSObject {
}

- (IBAction)openURL:(id)sender;
- (IBAction)openAboutPanel:(id)sender;

@end

@interface SDLApplication : NSApplication

@end
