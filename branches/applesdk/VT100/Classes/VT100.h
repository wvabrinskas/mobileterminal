// VT100.h
// MobileTerminal
//
// This file contains the bridge between the higher level text drawing
// controls and the lower level terminal state pieces (screen and terminal).
// The VT100 interface should be the only access from those components to the
// VT100 subsystem.  This layer mostly exists to keep the complexity/mess of
// the VT100Terminal and VT100 screen away from everything else.

#import <Foundation/Foundation.h>
#import "VT100Types.h"

// Forward declarations
@class VT100Terminal;
@class VT100Screen;

// VT100 is the public interface that combines the terminal subcomponents.  The
// caller is expected to provide the raw terminal data into the VT100 object
// via calls to handleInputStream.  VT100 exposes the contents of the screen by
// implementing the ScreenBuffer protocol.
@interface VT100 : NSObject <ScreenBuffer> {
@private
  VT100Screen* screen;
  VT100Terminal* terminal;
  id <ScreenBufferRefreshDelegate>* delegate;
}

// Initialize a VT100
- (id)init;

- (void)setRefreshDelegate:(id <ScreenBufferRefreshDelegate>)refreshDelegate;

// Reads raw character data into the terminal character processor.  This will
// almost certainly cause updates to the screen buffer.
- (void)readInputStream:(const char*)data withLength:(unsigned int)length;

// ScreenBuffer methods for obtaining information about the characters
// currently on the screen.
- (void)setScreenSize:(ScreenSize)size;
- (ScreenSize)screenSize;
- (screen_char_t*)bufferForRow:(int)row;

@end