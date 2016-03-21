
#import "ConsoleWindowController.h"

@interface ConsoleWindowController ()

@end

#define SKIP_LINES_COUNT    3
#define MAX_LINE_LEN        10240
#define MAX_LINES_COUNT     2000

@implementation ConsoleWindowController
@synthesize textView;

- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    if (self)
    {
        // Initialization code here.
        logs = [[NSMutableArray array] retain];
        linesCount = [[NSMutableArray arrayWithCapacity:MAX_LINES_COUNT + 1] retain];
    }

    return self;
}

- (void)dealloc
{
    [logs release];
    [linesCount release];
    [super dealloc];
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}

- (void) trace:(NSString*)msg
{
    [logs addObject:msg];
    
    if ([logs count] == 1) {
        [NSObject cancelPreviousPerformRequestsWithTarget:self];
        [self performSelector:@selector(updateTextView) withObject:nil afterDelay:0.1];
    }
}

- (void) updateTextView
{
    if (0 == [logs count]) {
        return;
    }
    NSFont *font = [NSFont fontWithName:@"Monaco" size:12.0];
    NSDictionary *attrsDictionary = [NSDictionary dictionaryWithObject:font forKey:NSFontAttributeName];
    
    for (int i = 0; i < [logs count]; i++) {
        NSString* msg = (NSString*)[logs objectAtIndex:i];
        if (traceCount >= SKIP_LINES_COUNT && [msg length] > MAX_LINE_LEN)
        {
            msg = [NSString stringWithFormat:@"%@ ...", [msg substringToIndex:MAX_LINE_LEN - 4]];
        }
        traceCount++;
        NSAttributedString *string = [[NSAttributedString alloc] initWithString:msg attributes:attrsDictionary];
        NSNumber *len = [NSNumber numberWithUnsignedInteger:[string length]];
        [linesCount addObject:len];
        
        NSTextStorage *storage = [textView textStorage];
        [storage beginEditing];
        [storage appendAttributedString:string];
        
        if ([linesCount count] >= MAX_LINES_COUNT)
        {
            len = [linesCount objectAtIndex:0];
            [storage deleteCharactersInRange:NSMakeRange(0, [len unsignedIntegerValue])];
            [linesCount removeObjectAtIndex:0];
        }
        [storage endEditing];
    }
    
    [logs removeAllObjects];

    [self changeScroll];
}

- (void) changeScroll
{
    BOOL scroll = [checkScroll state] == NSOnState;
    if(scroll)
    {
        [self.textView scrollRangeToVisible: NSMakeRange(self.textView.string.length, 0)];
    }
}

- (IBAction)onClear:(id)sender
{
    NSTextStorage *storage = [textView textStorage];
    [storage setAttributedString:[[[NSAttributedString alloc] initWithString:@""] autorelease]];
}

- (IBAction)onScrollChange:(id)sender
{
    [self changeScroll];
}

- (IBAction)onTopChange:(id)sender
{
    BOOL isTop = [topCheckBox state] == NSOnState;
    if(isTop)
    {
        [self.window setLevel:NSFloatingWindowLevel];
    }
    else
    {
        [self.window setLevel:NSNormalWindowLevel];
    }
}

@end
