//
//  PyramidRenderer.h
//  Pyramid
//
//  Created by Nneoma Osuji on 29/03/2024.
//

// PyramidRenderer.h

#import <Foundation/Foundation.h>

@class PyramidRenderer;

@protocol PyramidRendererDelegate <NSObject>

// Define any delegate methods here if needed

@end

@interface PyramidRenderer : NSObject

@property (nonatomic, weak) id<PyramidRendererDelegate> delegate;

- (void)renderPyramidWithRows:(int)rows;

@end

