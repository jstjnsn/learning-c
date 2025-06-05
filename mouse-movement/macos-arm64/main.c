#include <ApplicationServices/ApplicationServices.h>
#include <string.h>

CGEventRef mouseCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    if (type != kCGEventMouseMoved) {
        return event;
    }

    CGPoint location = CGEventGetLocation(event);
    printf("mouse: (x) %d (y) %d\n", (int)location.x, (int)location.y);

    return event;
}

int main() {
    CGRect bounds = CGDisplayBounds(CGMainDisplayID());

    printf("screen size is (w) %d by (h) %d\n", (int)bounds.size.width, (int)bounds.size.height);

    CFMachPortRef event = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault,
                                           (1 << kCGEventMouseMoved), mouseCallback, NULL);

    if (!event) {
        fprintf(stderr, "failed to create event tap\n");
        exit(1);
    }

    CFRunLoopSourceRef loopRef = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, event, 0);

    CFRunLoopAddSource(CFRunLoopGetCurrent(), loopRef, kCFRunLoopCommonModes);

    CGEventTapEnable(event, true);

    CFRunLoopRun();

    exit(0);
}