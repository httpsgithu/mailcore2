//
//  MCOMessageBuilder.h
//  mailcore2
//
//  Created by DINH Viêt Hoà on 3/22/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#ifndef __MAILCORE_MCOMESSAGEBUILDER_H_

#define __MAILCORE_MCOMESSAGEBUILDER_H_

#import <MailCore/MCOAbstractMessage.h>

/**
 This class will allow you to build a RFC 822 formatted message.
 For example when you need to send a message using SMTP,
 you need to generate first a RFC 822 formatted message.
 This class will help you do that.
 
    MCOMessageBuilder * builder = [[MCOMessageBuilder alloc] init];
    [[builder header] setFrom:[MCOAddress addressWithDisplayName:@"Hoa V. DINH" mailbox:@"hoa@etpan.org"];
    NSArray * to = [NSArray arrayWithObject:[MCOAddress addressWithDisplayName:@"Gael Roualland" mailbox:@"gael@etpan.org"]];
    [[builder header] setTo:to];
    [[builder header] setSubject:@"A nice picture!"];
    [builder setHTMLBody:@"<div>Here's the message I need to send.</div>"];
    [builder addAttachment:[MCOAttachment attachmentWithContentsOfFile:@"/Users/foo/Pictures/image.jpg"]];
    NSData * rfc822Data = [builder data];
 
*/

@class MCOAttachment;
@protocol MCOHTMLRendererDelegate;

@interface MCOMessageBuilder : MCOAbstractMessage <NSCopying>

/** Main HTML content of the message.*/
@property (nonatomic, copy, setter=setHTMLBody:) NSString * htmlBody;

/** Plain text content of the message.*/
@property (nonatomic, copy) NSString * textBody;

/** List of file attachments.*/
@property (nonatomic, copy) NSArray * /* MCOAttachment */ attachments;

/** List of related file attachments (included as cid: link in the HTML part).*/
@property (nonatomic, copy) NSArray * /* MCOAttachment */ relatedAttachments;

/** Prefix for the boundary identifier. Default value is nil.*/
@property (nonatomic, copy) NSString * boundaryPrefix;

/** Add an attachment.*/
- (void) addAttachment:(MCOAttachment *)attachment;

/** Add a related attachment.*/
- (void) addRelatedAttachment:(MCOAttachment *)attachment;

/** RFC 822 formatted message.*/
- (NSData *) data;

/** HTML rendering of the message to be displayed in a web view. The delegate can be nil.*/
- (NSString *) htmlRenderingWithDelegate:(id <MCOHTMLRendererDelegate>)delegate;

@end

#endif
