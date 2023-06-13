//
//  NSArray+HigherOrderFunctionsForADOP.h
//  Beequick
//
//  Created by fanpyi on 20/3/15.
//

#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"

#import <Foundation/Foundation.h>

@interface NSArray<T> (HigherOrderFunctionsForADOP)

-(NSArray *)mapForADOP:(id (^)(T obj))block;

-(id)reduceForADOP:(id)initial combine:(id (^)(id accumulator,T item))combine;

-(NSArray *)filterForADOP:(BOOL (^)(T obj))block;

-(BOOL)containsForADOP:(BOOL(^)(T obj))block;

- (NSArray *)flatMapForADOP:(id (^)(id obj))block;

@end
