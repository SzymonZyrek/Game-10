#import "Identifiable.h"

static unsigned long lastID;

@implementation Identifiable

+(long)getNextId
{
    return ++lastID;
}
-(id)init
{
    if (self= [super init])
    {
        self->_itsId = [Identifiable getNextId];
#ifdef __DEBUG_IDENTIFIABLES
        NSLog(@"Created Identifiable of class: %@, with id: %lu",[self class], _itsId);
#endif
    }
    return self;
}
+ (void)initialize {
    if (self == [Identifiable class]) {
        lastID = 0;
    }
}
@end
