#ifndef IMAGELIB_COMMON_H
#define IMAGELIB_COMMON_H

#include <PalmOS.h>
#include <PalmTypes.h>

#define ImageLibCreatorID 'imgL'
#define ImageLibTypeID    'libr'
#define ImageLibName      "ImageLibrary"


// Preview height and width in standard pixels. On a double density device,
// the bitmap returned would be twice these dimensions.
#define kPalmSizeImageWidth     160
#define kPalmSizeImageHeight    120
#define kFullSizeImageWidth     640
#define kFullSizeImageHeight    480
#define kThumbnailImageWidth     40
#define kThumbnailImageHeight    30
#define kPreviewBitmapWidth     (kPalmSizeImageWidth)
#define kPreviewBitmapHeight    (kPalmSizeImageHeight)

#define kInvalidRecIndex ((UInt16)0xFFFF )

#define kImageFilenameLength    (dmDBNameLength)



#define kNoSortOrder (0)
#define kSortByName  (1)
#define kSortByDate  (2)
#define kSortByNameDesc  (3)
#define kSortByDateDesc  (4)

#define kResizeOperation (0)
#define kJPEGOperation   (1)
#define kVFSOperation    (2)


typedef void * ImageIteratorHandle;
typedef void (*ImageLibProgressCallbackType) (Int32 progress, Int32 max, Int8 operation);


// Should this be in HsErrorClases.h? HS should define the error base
#define imageLibErrorClass  (appErrorClass | 0x1000)


#define imageLibErrBadParam             (imageLibErrorClass)
#define imageLibErrNoCamera             (imageLibErrorClass + 1)
#define imageLibErrInternalFailure      (imageLibErrorClass + 2)
#define imageLibErrWriteFailure         (imageLibErrorClass + 3)
#define imageLibErrReadFailure          (imageLibErrorClass + 4)
#define imageLibErrBadData              (imageLibErrorClass + 5)
#define imageLibErrBadImageType         (imageLibErrorClass + 6)
#define imageLibErrBadImageDepth        (imageLibErrorClass + 7)
#define imageLibErrBadDimensions        (imageLibErrorClass + 8)
#define imageLibErrInitializationFailed (imageLibErrorClass + 9)
#define imageLibErrBadColorspace        (imageLibErrorClass + 10) 
#define imageLibErrBadThumbnailType     (imageLibErrorClass + 11)
#define imageLibErrThumnailExists       (imageLibErrorClass + 12)
#define imageLibErrBadScaleFactor       (imageLibErrorClass + 13)
#define imageLibErrBadBitmapType        (imageLibErrorClass + 14)
#define imageLibErrImageAlreadyDownsized (imageLibErrorClass + 15)
#define imageLibErrImageLocked           (imageLibErrorClass + 16) 

#endif
