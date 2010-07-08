/**
 * @file 68k/Libraries/Imaging/ImageLib.h
 * @brief Imaging Library.
 *
 * This file contains routines for capturing, storing, iterating, resizing, and
 * manipulating images. The imaging library is a client of both the camera
 * driver and the JPEG library.
 *
 * @license
 * Copyright (c) 2003 IDEO. All rights reserved.
 * Portions ©2003 Handspring, Inc. All rights reserved.
 *
 * @author    Harold Howe
 *   
 * $Id:$
 *
 ****************************************************************/

#ifndef IMAGELIB_H
#define IMAGELIB_H

#include <PalmOS.h>
#include <PalmTypes.h>
#include <VFSMgr.h>



#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************/
/* ImageLibOpen */
/**
 * @brief Library open routine
 *
 * Library open call for 68k clients of the library. This routine maps to the
 * sysLibTrapOpen trap.
 *
 * @param   libRef IN  Library reference number.
 *
 * @retval  Err        0 on success or error code on failure.
 *
 * @note
 * It is customary for shared libraries to provide open and close functions.
 * The open and close functions in ImageLib are empty stubs that exist for the
 * sole purpose of adhering to past convention. This function does nothing and
 * will always return errNone. All library initialization is done from
 * PilotMain.
 *
 * @note This function is not available to ARM clients of the library.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibOpen(UInt16 libRef) SYS_TRAP(kImageLibTrapOpen );


/****************************************************************/
/* ImageLibClose */
/**
 * @brief Library close routine
 *
 * Library close function for 68k clients of the library. This routine maps to
 * the sysLibTrapClose trap.
 *
 * @param   libRef IN  Library reference number.
 *
 * @retval  Err        0 on success or error code on failure.
 *
 * @note
 * This function is an empty stub (see comments for ImageLibOpen). All library
 * cleanup is done from PilotMain.
 *
 * @note This function is not available to ARM clients of the library.
 *
 * @see ImageLibOpen
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibClose(UInt16 libRef) SYS_TRAP(kImageLibTrapClose);


/****************************************************************/
/* ImageLibGetVersion */
/**
 * @brief Retrieves the version number of the image library.
 *
 * @param   libRef IN       Library reference number.
 * @param   dwVerP OUT      Pointer to library version variable. *
 *
 * @retval  Err        0 on success or error code on failure.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibGetVersion(UInt16 libRef, UInt32 *dwVerP)
    SYS_TRAP(kImageLibTrapGetVersion);


/****************************************************************/
/* ImageLibCameraExists */
/**
 * @brief Detects presence of camera driver.
 *
 * The imaging library loads the camera driver dynamically. If the driver was
 * found and was loaded successfully, ImageLibCameraExists writes true to
 * existsP, otherwise it writes false.
 *
 * @param   libRef   IN   Library reference number.
 * @param   existsP  OUT  true if camera successfully loaded. Otherwise false.
 * @retval  Err        0 on success or error code on failure.
 *
 * @note This routine will attempt to load the camera driver if it hasn't
 * already been loaded. The driver will remain loaded until the imaging library
 * is unloaded, or until ImageLibTurnCameraOff is called.
 *
 * @see ImageLibTurnCameraOff
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibCameraExists(UInt16 libRef, Boolean* existsP)
    SYS_TRAP(kImageLibTrapCameraExists);

/****************************************************************/
/* ImageLibImageCapture */
/**
 * @brief Captures an image and stores it in the database.
 *
 * @param   libRef              IN   Library reference number.
 * @param   fullsize            IN   true capture a 640x480 image. false to capture 160x120
 * @param   playShutterSound    IN   true to play a camera shutter sound.
 * @param   drawImmediately     IN   true to immediately draw the captured image to the current draw window.
 * @param   x                   IN   x location to draw the captured image. Relative to the current draw window. Ignored if drawImmediately is false.
 * @param   y                   IN   y location to draw the captured image. Relative to the current draw window. Ignored if drawImmediately is false.
 * @param   newRecNoP           OUT  index of the new image. If the capture fails, kInvalidRecIndex is written to this value. Pass NULL if you don’t care what the new index is.
 * @retval  Err        0 on success or error code on failure.
 *
 * @note Images are appended to the end of the database.
 *
 * @note The camera driver always captures 640x480 images. If fullSize is false,
 * the data from the camera is downsampled to 160x120 using a filtering
 * algorithm.
 *
 * @note Captures are currently done in 16 bit RGB mode. Capturing an image
 * requires at least 600 kB of free space in the dynamic heap (640x480x2).
 *
 * @note Captured pictures are stored in uncompressed palmOS bitmap format. They
 * have To compress an
 * image as a JPEG, call ImageLibImageSave.
 *
 * @see ImageLibImageSave
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibImageCapture(UInt16 libRef,
                         Boolean fullsize,
                         Boolean playShutterSound,
                         Boolean drawImmediately,
                         Coord x,
                         Coord y,
                         UInt16 *newRecNoP)
    SYS_TRAP(kImageLibTrapImageCapture);


/****************************************************************/
/* ImageLibImageSave */
/**
 * @brief Compresses a captured image to JPEG format.
 *
 * Compresses a captured image to JPEG, sets the image name, and sets the
 * category of the picture. After saving, the uncompressed bitmap data is
 * discarded and replaced with the JPEG version of the image.
 *
 * @param   libRef              IN   Library reference number.
 * @param   recIndex            IN   Index of the image to compress.
 * @param   name                IN   Name of the picture
 * @param   category            IN   Category to store the image in
 * @retval  Err        0 on success or error code on failure.
 *
 * @note This routine should only be invoke on newly captured images, and it
 * should only be called once per picture.
 *
 * @see ImageLibImageCapture
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibImageSave(UInt16 libRef,UInt16 recIndex,
                      const char * name, UInt16 category)
    SYS_TRAP(kImageLibTrapImageSave);


/****************************************************************/
/* ImageLibPreviewBitmapCreate */
/**
 * @brief Creates a bitmap for storing preview images from the camera.
 *
 * Creates a preview bitmap. If Compresses a captured image to JPEG, sets the image name, and sets the
 * category of the picture. After saving, the uncompressed bitmap data is
 * discarded and replaced with the JPEG version of the image.
 *
 * @param   libRef              IN   Library reference number.
 * @param   errP                OUT  0 on success, non-zero on error. This parameter should not be null.
 * @retval  BitmapType *        On success, the result is a new 160x120 bitmap whose bit depth matches
 * the bit depth of the screen. On failure, the result is NULL
 *
 * @note When called from a 68k application, the return value should be treated
 * as opaque. The bitmap can safely be passed to the Palm OS bitmap routines,
 * but 68k applications should not attempt to dereference members of the bitmap
 * structure directly.
 *
 * @note Bitmaps created with this function should be disposed of by calling
 * ImageLibBitmapDelete. Do note call BmpDelete or MemPtrFree.
 *
 * @note If an error occurs, this function returns NULL and writes an error code
 * to errP. If the function returns a non-NULL bitmap value, then *errP will
 * always be 0.
 *
 * @note This function does not perform an image preview. The resulting bitmap
 * is empty. To fill the bitmap with a preview image, pass it to
 * ImageLibPreviewBitmapFill.
 *
 * @see ImageLibPreviewBitmapFill
 * @see ImageLibBitmapDelete
 *
 * @author Harold Howe
 *
 ****************************************************************/
BitmapType* ImageLibPreviewBitmapCreate(UInt16 libRef, Err *errP)
    SYS_TRAP(kImageLibTrapPreviewBitmapCreate);

/****************************************************************/
/* ImageLibPreviewBitmapFill */
/**
 * @brief Fills a bitmap with a preview image from the camera.
 *
 * @param   libRef              IN   Library reference number.
 * @param   imageP              IN/OUT  Bitmap to fill with a preview.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note The imageP argument should represent a bitmap created with
 * ImageLibPreviewBitmapCreate.
 *
 * @see ImageLibPreviewBitmapCreate
 * @see ImageLibBitmapDelete
 * @see ImageLibPreviewStop
 * @see ImageLibPreviewStart
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibPreviewBitmapFill(UInt16 libRef, BitmapType* imageP)
    SYS_TRAP(kImageLibTrapPreviewBitmapFill);


/****************************************************************/
/* ImageLibPreviewDraw */
/**
 * @brief Draws a preview image to the current draw window.
 *
 * Snaps a preview image with the camera driver and then draws it to the
 * current draw window at x,y. x and y are relative coordinates.
 *
 * @param   libRef              IN Library reference number.
 * @param   x                   IN x location to draw the preview image, relative to the current draw window.
 * @param   y                   IN y location to draw the preview image, relative to the current draw window.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @see ImageLibPreviewStop
 * @see ImageLibPreviewStart
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibPreviewDraw(UInt16 libRef, Coord x, Coord y)
    SYS_TRAP(kImageLibTrapPreviewDraw);



/****************************************************************/
/* ImageLibImageBitmapCreate */
/**
 * @brief Creates a bitmap for viewing an image from the database.
 *
 * Creates a 16 bit bitmap for holding an image from the database. If
 * recIndex is a valid image index, that image is loaded into the resulting
 * bitmap. Otherwise, the result is an empty picture.
 *
 * @param   libRef              IN  Library reference number.
 * @param   recIndex            IN  index of image to fill bitmap with. Use kInvalidRecIndex to create an empty 160x120, 16 bit bitmap.
 * @PARAM   errP                OUT If the function succeeds, 0 is written to errP. Otherwise, a non-zero error code is written. This parameter should not be NULL.
 * @retval  BitmapType *        On success, the result is a new bitmap with a bit depth of 16. On error, the result is NULL.
 *
 * @note When called from a 68k application, the return value should be treated
 * as opaque. The bitmap can safely be passed to the Palm OS bitmap routines,
 * but 68k applications should not attempt to dereference members of the bitmap
 * structure directly.
 *
 * @note Bitmaps created with this function should be disposed of by calling
 * ImageLibBitmapDelete. Do note call BmpDelete or MemPtrFree.
 *
 * @note If an error occurs, this function returns NULL and writes an error code
 * to errP. If the function returns a non-NULL bitmap value, then *errP will
 * always be 0.
 *
 * @note If recIndex is kInvalidRecIndex, the result is an empty 160x120 bitmap.
 * If recIndex is not kInvalidRecIndex, the result is a bitmap that contains the
 * given image from the database. The returned bitmap will be 160x120 if the
 * image in the database is 160x120, 320x240, 640x480, or any other image larger
 * than 160x120 with a 4:3 aspect ratio. If the image has a non-standard size,
 * it is downsized to fit in a 160x120 box. The aspect ratio of the picture is
 * preserved. Images that are less than 160x120 are not scaled at all.
 *
 * @see ImageLibBitmapDelete
 * @see ImageLibPreviewStop
 * @see ImageLibPreviewStart
 *
 * @author Harold Howe
 *
 ****************************************************************/
BitmapType* ImageLibImageBitmapCreate(UInt16 libRef,
                                      UInt16 recIndex,
                                      Err *errP)
    SYS_TRAP(kImageLibTrapImageBitmapCreate);


/****************************************************************/
/* ImageLibImageBitmapFill */
/**
 * @brief Fills a bitmap with an image from the database.
 *
 *
 * @param   libRef              IN  Library reference number.
 * @param   recIndex            IN  index of image to fill bitmap with.
 * @param   imageP              IN/OUT  Bitmap to fill.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note The imageP argument should represent a bitmap created with
 * ImageLibImageBitmapCreate.
 *
 * @note The image from the database is resampled as necessary to fit the
 * dimensions of imageP. When the image is a jpeg, the DCT scaling features of
 * the IJG library are used to get the image size close to the destination size.
 * From there, the image is resampled with a filter to match the dimensions of
 * imageP. If the aspect ratio of imageP does not match the aspect ratio of
 * the picture, the picture is stretched to fit.
 *
 * @see ImageLibImageBitmapCreate
 * @see ImageLibBitmapDelete
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibImageBitmapFill(UInt16 libRef, UInt16 recIndex, BitmapType* imageP)
    SYS_TRAP(kImageLibTrapImageBitmapFill);

/****************************************************************/
/* ImageLibImageDraw*/
/**
 * @brief Draws an image from the database to the current draw window.
 *
 * Draws an image from the database to the current draw window at x,y. x and y
 * are window relative coordinates.
 *
 * @param   libRef              IN  Library reference number.
 * @param   recIndex            IN  index of image to draw.
 * @param   x                   IN  x location to draw the preview image, relative to the current draw window.
 * @param   y                   IN  y location to draw the preview image, relative to the current draw window.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note If necessary, the image is downsized to fit in a 160x120 box. The
 * aspect ratio of the picture is preserved.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibImageDraw(UInt16 libRef, UInt16 recIndex, Coord x, Coord y)
    SYS_TRAP(kImageLibTrapImageDraw);


/****************************************************************/
/* ImageLibThumbnailBitmapCreate */
/**
 * @brief Creates a bitmap for viewing an thumbnail for an image in the database.
 *
 * Creates a 16 bit bitmap for holding an thumbnail image . If
 * recIndex is a valid image index, the thumbnail for that image is loaded into
 * the resulting bitmap. Otherwise, the result is an empty bitmap.
 *
 * @param   libRef              IN  Library reference number.
 * @param   recIndex            IN  index of image to fill the thumbnail bitmap with. Use kInvalidRecIndex to create an empty 40x30, 16 bit bitmap.
 * @PARAM   errP                OUT If the function succeeds, 0 is written to errP. Otherwise, a non-zero error code is written. This parameter should not be NULL.
 * @retval  BitmapType *        On success, the result is a new bitmap with a bit depth of 16. On error, the result is NULL.
 *
 * @note When called from a 68k application, the return value should be treated
 * as opaque. The bitmap can safely be passed to the Palm OS bitmap routines,
 * but 68k applications should not attempt to dereference members of the bitmap
 * structure directly.
 *
 * @note Bitmaps created with this function should be disposed of by calling
 * ImageLibBitmapDelete. Do note call BmpDelete or MemPtrFree.
 *
 * @note If an error occurs, this function returns NULL and writes an error code
 * to errP. If the function returns a non-NULL bitmap value, then *errP will
 * always be 0.
 *
 * @note The thumbnail is generated on the fly if the image in the database
 * does not have a thumbnail record.
 *
 * @see ImageLibBitmapDelete
 *
 * @author Harold Howe
 *
 ****************************************************************/
BitmapType* ImageLibThumbnailBitmapCreate(UInt16 libRef,
                                          UInt16 recIndex,
                                          Err *errP)
    SYS_TRAP(kImageLibTrapThumbnailBitmapCreate);


/****************************************************************/
/* ImageLibThumbnailBitmapFill*/
/**
 * @brief Fills a bitmap with an thumbnail image from the database.
 *
 *
 * @param   libRef              IN  Library reference number.
 * @param   recIndex            IN  index of image
 * @param   imageP              IN/OUT  Bitmap to fill.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note The imageP argument should represent a bitmap created with
 * ImageLibThumbnailBitmapCreate.
 *
 * @note The image from the database is resampled as necessary to fit the
 * dimensions of imageP. If the aspect ratio of imageP does not match the aspect
 * ratio of the picture, the picture is stretched to fit.
 *
 * @see ImageLibThumbnailBitmapCreate
 * @see ImageLibBitmapDelete
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibThumbnailBitmapFill(UInt16 libRef, UInt16 recIndex, BitmapType* imageP)  SYS_TRAP(kImageLibTrapThumbnailBitmapFill);


/****************************************************************/
/* ImageLibThumbnailDraw*/
/**
 * @brief Draws an thumbnail to the current draw window.
 *
 * Draws an thumbnail image from the database to the current draw window at x,y.
 * x and y * are window relative coordinates.
 *
 * @param   libRef              IN  Library reference number.
 * @param   recIndex            IN  index of image
 * @param   x                   IN  x location to draw the preview image, relative to the current draw window.
 * @param   y                   IN  y location to draw the preview image, relative to the current draw window.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibThumbnailDraw(UInt16 libRef, UInt16 recIndex, Coord x, Coord y)
    SYS_TRAP(kImageLibTrapThumbnailDraw);


/****************************************************************/
/* ImageLibBitmapDelete*/
/**
 * @brief Deletes a bitmap created by the library.
 *
 * Use ImageLibBitmapDelete to delete any bitmap that was created and returned
 * by the imaging library (ImageLibPreviewBitmapCreate, ImageLibImageBitmapCreate and ImageLibThumbnailBitmapCreate).
 *
 * @param   libRef              IN  Library reference number.
 * @param   bmp                 IN  Bitmap to delete.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibBitmapDelete(UInt16 libRef, BitmapType *bmp)
    SYS_TRAP(kImageLibTrapBitmapDelete);

/****************************************************************/
/* ImageLibDeleteImage*/
/**
 * @brief Delete a picture from the database.
 *
 * This routine deletes an image and its thumbnail from the database.
 *
 * @param   libRef              IN  Library reference number.
 * @param   recIndex            IN  index of image to delete.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note Deleting a picture invalidates the record indices of all subsequent
 * images in the database. Records are deleted with DmRemoveRecord. They are
 * not archived.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibDeleteImage(UInt16 libRef, UInt16 recIndex)
    SYS_TRAP(kImageLibTrapDeleteImage);

/****************************************************************/
/* ImageLibResizeImage*/
/**
 * @deprecated
 * @brief Resizes a fullsize picture in the database to 160x120 (palm size).
 *
 * Resizes a fullsize picture in the database to 160x120 (palm size). The original
 * fullsize image is replaced with the palm size version.
 *
 * @param   libRef              IN  Library reference number.
 * @param   recIndex            IN  index of image to resize.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note If the original image is a full size 640x480 jpeg, the image is
 * downsampled using the DCT scaling features of the IJG library. This means
 * that the JPEG is decompressed directly to 160x120, and then compressed again
 * and saved back to the database.
 *
 * @note If the original image is not a 640x480 jpeg, it is scaled as much as
 * possible using the IJG scaling features. After decompression, the picture is
 * resampled with a filter to get its dimensions to 160x120.
 *
 * @note ImageLibResizeImage is deprecated. Use ImageLibResize instead.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibResizeImage(UInt16 libRef, UInt16 recIndex)
    SYS_TRAP(kImageLibTrapResizeImage);


/****************************************************************/
/* ImageLibGetImageDatabases*/
/**
 * @brief Return the references to the database that are used to store pictures.
 *
 * @param   libRef              IN  Library reference number.
 * @param   dbMainP             OUT Reference to the main database. Pass NULL for this parameter if you don’t want to retrieve it.
 * @param   dbNoteP             OUT Reference to the note database. Pass NULL for this parameter if you don’t want to retrieve it.
 * @param   dbImageP            OUT Reference to the images database.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note The image library opens each database when it is loaded, and closes them when it is unloaded.
 * Do not close the database references that are returned by this function because the references are still being used by
 * the imaging library.
 *
 * @note The data in each database is stored in little endian format.
 *
 * @note The main database contains one record for each image in the database.
 * Each record has a fixed size and contains information about the picture. The
 * image database contains the actual JPEG data for each image. The main
 * database acts as a master table and the images database is a child table.
 *
 * @note The notes database is not currently used.
 *
 * @note The category of an image is determined by the category of its record in
 * the main database. Categories are not used in the image table.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibGetImageDatabases(UInt16 libRef, DmOpenRef *dbMainP,
                              DmOpenRef *dbNoteP, DmOpenRef *dbImageP)
    SYS_TRAP(kImageLibTrapGetImageDatabases);


/****************************************************************/
/* ImageLibGetImageInfo*/
/**
 * @brief Retrieves information about an image stored in the database.
 *
 * @param   libRef              IN  Library reference number.
 * @param   recIndex            IN  Index of the picture
 * @param   name                OUT Buffer to receive the name of the image. The buffer should be at least 32
                                    characters long (31 + null terminator). Pass NULL for this parameter if you don't want to retrieve it.
 * @param   fullSizeP           OUT true if image is 640x480, false if palm size. Pass NULL for this parameter if you don't want to retrieve it.
 * @param   createdP            OUT Timestamp when picture was creatd. Pass NULL for this parameter if you don't want to retrieve it.
 * @param   sizeP               OUT Size of the image data in bytes. Pass NULL for this parameter if you don't want to retrieve it.
 * @param   categoryP           OUT Category that that picture is assigned to. Pass NULL for this parameter if you don't want to retrieve it.
 * @param   categoryName        OUT Text description of the picture's category (ie 'Unfiled'). Pass NULL for this parameter if you don't want to retrieve it.
 * @param   lockedP             OUT true if image is locked.
 * @param   uidP                OUT Unique ID of the image.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibGetImageInfo(UInt16 libRef, UInt16 recIndex, Char* name,
                         Boolean* fullSizeP, UInt32* createdP, UInt32* sizeP,
                         UInt16* categoryP, Char* categoryName, Boolean *lockedP, UInt32 *uidP) SYS_TRAP(kImageLibTrapGetImageInfo);

/****************************************************************/
/* ImageLibSetImageInfo*/
/**
 * @brief Assigns information about an image stored in the database.
 *
 * @param   libRef              IN  Library reference number.
 * @param   recIndex            IN  Index of the picture
 * @param   name                IN  Name of the picture. Pass NULL for this parameter if you don't want to set it.
 * @param   categoryP           OUT Category that that picture is assigned to. Pass NULL for this parameter if you don't want to set it.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibSetImageInfo(UInt16 libRef, UInt16 recIndex,
                         const char* name, UInt16* categoryP)                   SYS_TRAP(kImageLibTrapSetImageInfo);


/****************************************************************/
/* ImageLibCopyImageToVFS*/
/**
 * @brief Copies an image from the database to a VFS volume.
 *
 * Copies an image from the database to a VFS volume, overwriting any previous
 * file that existed on the volume with the same name.
 *
 * @param   libRef              IN  Library reference number.
 * @param   recIndex            IN  Index of the picture
 * @param   volRefNum           IN  Ref number of the VFS volume
 * @param   fileName            IN  Filename of the image (ie "/DCIM/picture.jpg")
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note volRefNum should be obtained via a call to VFSVolumeEnumerate
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibCopyImageToVFS(UInt16 libRef, UInt16 recIndex,
                           UInt16 volRefNum, const char* fileName)
    SYS_TRAP(kImageLibTrapCopyImageToVFS);


/****************************************************************/
/* ImageLibCopyImageToVFS*/
/**
 * @brief Copies an image from a VFS volume to the database.
 *
 * @param   libRef              IN  Library reference number.
 * @param   volRefNum           IN  Ref number of the VFS volume
 * @param   fileName            IN  Filename of the image (ie "/DCIM/picture001.jpg")
 * @param   name                IN  Name of the image in the database (ie "picture001")
 * @param   category            IN  Category that the image should be assigned to
 * @param   newRecIndexP        OUT Record index of the newly stored picture. Pass NULL if you don't care what the new index is.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note volRefNum should be obtained via a call to VFSVolumeEnumerate
 *
 * @note If a picture with a matching name and category already exists in the
 * database, that image is <b>not</b> overwritten. After the call, there will
 * be two images with the same name and category.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibCopyImageFromVFS(UInt16 libRef, UInt16 volRefNum,
                             const char* fileName, const char * name,
                             UInt16 category, UInt16 *newRecIndexP)
    SYS_TRAP(kImageLibTrapCopyImageFromVFS);


/****************************************************************/
/* ImageLibImageBitmapCreateFromVFS */
/**
 * @brief Creates a bitmap for viewing an image from a VFS volume.
 *
 * Creates a 16 bit bitmap for holding an image from a VFS volume. The library
 * decompresses the image from the volume and stores it in the result.
 *
 * @param   libRef              IN  Library reference number.
 * @param   volRefNum           IN  Ref number of the VFS volume
 * @param   fileName            IN  Filename of the image (ie "/DCIM/picture.jpg")
 * @PARAM   errP                OUT If the function succeeds, 0 is written to errP. Otherwise, a non-zero error code is written. This parameter should not be NULL.
 * @retval  BitmapType *        On success, the result is a new bitmap with a bit depth of 16. On error, the result is NULL.
 *
 * @note When called from a 68k application, the return value should be treated
 * as opaque. The bitmap can safely be passed to the Palm OS bitmap routines,
 * but 68k applications should not attempt to dereference members of the bitmap
 * structure directly.
 *
 * @note Bitmaps created with this function should be disposed of by calling
 * ImageLibBitmapDelete. Do note call BmpDelete or MemPtrFree.
 *
 * @note If an error occurs, this function returns NULL and writes an error code
 * to errP. If the function returns a non-NULL bitmap value, then *errP will
 * always be 0.
 *
 * @note The picture is always resized to fit in a 160x120 box. If the image needs
 * to be resized, its aspect ratio is maintained.
 *
 * @see ImageLibBitmapDelete
 *
 * @author Harold Howe
 *
 ****************************************************************/
BitmapType* ImageLibImageBitmapCreateFromVFS(UInt16 libRef, UInt16 volRefNum,
                                             const char* fileName, Err *errP)
    SYS_TRAP(kImageLibTrapImageBitmapCreateFromVFS);


/****************************************************************/
/* ImageLibImageBitmapFillFromVFS */
/**
 * @brief Fills a bitmap with an image from a VFS volume. *
 *
 * Fills a 16 bit bitmap with an image from a VFS volume. The library
 * decompresses the image from the volume and stores it in the supplied bitmap.
 * The image is resized to fit the dimensions of the supplied bitmap.
 *
 * @param   libRef              IN  Library reference number.
 * @param   volRefNum           IN  Ref number of the VFS volume
 * @param   fileName            IN  Filename of the image (ie "/DCIM/picture001.jpg")
 * @param   imageP              IN/OUT  Bitmap to fill.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note The imageP argument should represent a bitmap created with
 * ImageLibImageBitmapCreate or ImageLibImageBitmapCreateFromVFS.
 *
 * @note The image is resampled as necessary to fit the
 * dimensions of imageP. When the image is a jpeg, the DCT scaling features of
 * the IJG library are used to get the image size close to the destination size.
 * From there, the image is resampled with a filter to match the dimensions of
 * imageP. If the aspect ratio of imageP does not match the aspect ratio of
 * the picture, the picture is stretched to fit.
 *
 *
 * @see ImageLibImageBitmapCreate
 * @see ImageLibImageBitmapCreateFromVFS
 * @see ImageLibBitmapDelete
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibImageBitmapFillFromVFS(UInt16 libRef, UInt16 volRefNum,
                                   const char* fileName, BitmapType* imageP)
    SYS_TRAP(kImageLibTrapImageBitmapFillFromVFS);


/****************************************************************/
/* ImageLibImageDrawFromVFS*/
/**
 * @brief Draws an image from a VFS volume to the current draw window.
 *
 * Draws an image from from a VFS volume to the current draw window at x,y.
 * x and y are window relative coordinates.
 *
 * @param   libRef              IN  Library reference number.
 * @param   volRefNum           IN  Ref number of the VFS volume
 * @param   fileName            IN  Filename of the image (ie "/DCIM/picture001.jpg")
 * @param   x                   IN  x location to draw the image, relative to the current draw window.
 * @param   y                   IN  y location to draw the image, relative to the current draw window.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note If necessary, the image is downsized to fit in a 160x120 box. The
 * aspect ratio of the picture is preserved.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibImageDrawFromVFS(UInt16 libRef, UInt16 volRefNum,
                             const char* fileName, Coord x, Coord y)
    SYS_TRAP(kImageLibTrapImageDrawFromVFS);


/****************************************************************/
/* ImageLibThumbnailBitmapCreateFromVFS */
/**
 * @brief Creates a bitmap for viewing an thumbnail for an image on a VFS volume.
 *
 * Creates a 16 bit bitmap for holding an thumbnail image for a VFS JPEG.
 *
 * @param   libRef              IN  Library reference number.
 * @param   volRefNum           IN  Ref number of the VFS volume
 * @param   fileName            IN  Filename of the image (ie "/DCIM/picture001.jpg")
 * @PARAM   errP                OUT If the function succeeds, 0 is written to errP. Otherwise, a non-zero error code is written. This parameter should not be NULL.
 * @retval  BitmapType *        On success, the result is a new bitmap with a bit depth of 16. On error, the result is NULL.
 *
 * @note When called from a 68k application, the return value should be treated
 * as opaque. The bitmap can safely be passed to the Palm OS bitmap routines,
 * but 68k applications should not attempt to dereference members of the bitmap
 * structure directly.
 *
 * @note Bitmaps created with this function should be disposed of by calling
 * ImageLibBitmapDelete. Do note call BmpDelete or MemPtrFree.
 *
 * @note If an error occurs, this function returns NULL and writes an error code
 * to errP. If the function returns a non-NULL bitmap value, then *errP will
 * always be 0.
 *
 * @note The thumbnail is generated on the fly from VFS file. For large images,
 * this operation can be slow.
 *
 * @see ImageLibBitmapDelete
 *
 * @author Harold Howe
 *
 ****************************************************************/
BitmapType* ImageLibThumbnailBitmapCreateFromVFS (UInt16 libRef,
                                                  UInt16 volRefNum,
                                                  const char* fileName,
                                                  Err *errP)
    SYS_TRAP(kImageLibTrapThumbnailBitmapCreateFromVFS);


/****************************************************************/
/* ImageLibImageBitmapFillFromVFS */
/**
 * @brief Fills a bitmap with a thumbnail image from a VFS volume. *
 *
 * @param   libRef              IN  Library reference number.
 * @param   volRefNum           IN  Ref number of the VFS volume
 * @param   fileName            IN  Filename of the image (ie "/DCIM/picture001.jpg")
 * @param   imageP              IN/OUT  Bitmap to fill.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note The imageP argument should represent a bitmap created with
 * ImageLibThumbnailBitmapCreate or ImageLibThumbnailBitmapCreateFromVFS.
 *
 * @note The image is resampled as necessary to fit the
 * dimensions of imageP.
 *
 *
 * @see ImageLibThumbnailBitmapCreate
 * @see ImageLibThumbnailBitmapCreateFromVFS
 * @see ImageLibBitmapDelete
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibThumbnailBitmapFillFromVFS(UInt16 libRef, UInt16 volRefNum,
                                       const char* fileName, BitmapType* imageP)
    SYS_TRAP(kImageLibTrapThumbnailBitmapFillFromVFS);

/****************************************************************/
/* ImageLibThumbnailDrawFromVFS*/
/**
 * @brief Draws an thumbnail from a VFS image to the current draw window.
 *
 * Draws an thumbnail image from a VFS image to the current draw window at x,y.
 * x and y * are window relative coordinates.
 *
 * @param   libRef              IN  Library reference number.
 * @param   volRefNum           IN  Ref number of the VFS volume
 * @param   fileName            IN  Filename of the image (ie "/DCIM/picture001.jpg")
 * @param   x                   IN  x location to draw the preview image, relative to the current draw window.
 * @param   y                   IN  y location to draw the preview image, relative to the current draw window.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibThumbnailDrawFromVFS(UInt16 libRef, UInt16 volRefNum, const char* fileName, Coord x, Coord y)   SYS_TRAP(kImageLibTrapThumbnailDrawFromVFS);


/****************************************************************/
/* ImageLibDoAttachImageDialog*/
/**
 * @brief Displays the attach image dialog.
 *
 * Displays the attach image dialog. Allows to user to select a picture from a
 * list. After choosing an image, the selection is written to the output
 * parameters recIndexP, volRefNum, and filename.
 *
 * @param   libRef              IN  Library reference number.
 * @param   recIndexP           OUT If the user selects an image from the database, recIndexP will contain the index of the image. If the user selects an image from a VFS volume, or they cancel the dialog, or an error occurs, recIndexP will contain kInvalidRecIndex.
 * @param   volRefNumP          OUT If the user selects an image from the VFS system, volRefNumP will contain the volume ref number of the selected image. In all other cases, volRefNumP will contain vfsInvalidVolRef.
 * @param   fileName            OUT If the user selects an image from the VFS system, the full path of the file will be copied into fileNameP. fileName should be capable of holding the largest possible VFS filename. If the user does not select a VFS file, fileName[0] will be \0.
 * @param   initialCategory     IN  The initial category that should be highlighted in the category dropdown. Pass 0 for unfiled. Pass dmAllCategories to show all pictures from the database.
 * @param   showConfirmation    IN  If true, a confirmation dialog will be displayed that shows the image in full size. If false, the confirmation dialog is skipped.
 * @param   internalImagesOnly  IN  If true, images from VFS volumes are not displayed to the user.
 * @param   dialogTitle         IN  The string to display as the title of the dialog. Pass null to display a localized default.
 * @param   btnTitle            IN  The string to display as the title of the OK button. Pass null to display a localized default.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note If the user cancels the dialog, the return value is still 0. The values
 * in recIndexP and volRefNumP indicate that the dialog was cancelled.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibDoAttachImageDialog(UInt16 libRef,
                                UInt16 *recIndexP,
                                UInt16 *volRefNumP,
                                char* fileName,
                                UInt16 initialCategory,
                                Boolean showConfirmation,
                                Boolean internalImagesOnly,
                                const char *dialogTitle,
                                const char * btnTitle)
    SYS_TRAP(kImageLibTrapDoAttachImageDialog);


/****************************************************************/
/* ImageLibCopyImageToBuffer*/
/**
 * @brief Copies a JPEG from the image database to a chunk of memory.
 *
 * Copies a JPEG from the image database to a chunk of memory at bufP. The
 * allocated memory block must be large enough to hold the entire blob of JPEG
 * data. The size of the JPEG can be determined with ImageLibGetImageInfo.
 *
 * @param   libRef              IN  Library reference number.
 * @param   recIndex            IN  Index of the picture
 * @param   bufP                IN/OUT Pointer to the block of memory that should receive the image.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note Fullsize images may requires that bufP be larger than 64 kB. Use
 * FtrPtrNew or MemChunkNew to create buffers larger than 64 kB. Otherwise,
 * consider using ImageLibCopyImageToFile instead.
 *
 * @see ImageLibGetImageInfo
 * @see ImageLibCopyImageToFile 
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibCopyImageToBuffer (UInt16 libRef, UInt16 recIndex, MemPtr bufP)
    SYS_TRAP(kImageLibTrapCopyImageToBuffer     );


/****************************************************************/
/* ImageLibCopyImageToFile*/
/**
 * @brief Copies a JPEG from the image database to a Palm OS file stream.
 *
 * Copies a JPEG from the image database to a Palm OS file stream. The library
 * writes to the file stream at its current postion. When done, the library
 * leaves the file handle pointing to the end of the file. To see the jpeg data,
 * the file handle should be rewound to its original location.
 *
 * @param   libRef              IN  Library reference number.
 * @param   recIndex            IN  Index of the picture
 * @param   fileH               IN  Handle to an open file stream.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibCopyImageToFile (UInt16 libRef, UInt16 recIndex, FileHand fileH)
    SYS_TRAP(kImageLibTrapCopyImageToFile);


/****************************************************************/
/* ImageLibInsertImageFromBuffer*/
/**
 * @brief Insert an image into the database from a memory buffer.
 *
 * Inserts a JPEG blob into the image database, storing it with the supplied
 * name and category.
 *
 * @param   libRef              IN  Library reference number.
 * @param   bufP                IN  Pointer to a JPEG image in memory.
 * @param   size                IN  Size of the source image in bytes.
 * @param   name                IN  Name of the new image (ie "Picture001")
 * @param   category            IN  The category to store the image in. Pass 0 for unfiled.
 * @param   newRecIndexP        OUT Index of the newly created image. Pass NULL if you don’t care about this value.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibInsertImageFromBuffer(UInt16 libRef, MemPtr bufP, UInt32 size,
                                  const char * name, UInt16 category,
                                  UInt16 *newRecIndexP)
    SYS_TRAP(kImageLibTrapInsertImageFromBuffer );


/****************************************************************/
/* ImageLibInsertImageFromBuffer*/
/**
 * @brief Insert an image into the database from a Palm OS file stream.
 *
 * Insert an image into the database from a Palm OS file stream. The file stream
 * is read from its current position to the end of the stream. When the routine
 * is finished, it leaves the stream open and performs a FileSeek back to the
 * original position.
 *
 * @param   libRef              IN  Library reference number.
 * @param   fileH               IN  Handle to an open file stream that contains a JPEG starting at its current position.
 * @param   name                IN  Name of the new image (ie "Picture001")
 * @param   category            IN  The category to store the image in. Pass 0 for unfiled.
 * @param   newRecIndexP        OUT Index of the newly created image. Pass NULL if you don’t care about this value.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibInsertImageFromFile(UInt16 libRef, FileHand fileH,
                               const char * name, UInt16 category,
                               UInt16 *newRecIndexP)
    SYS_TRAP(kImageLibTrapInsertImageFromFile   );


/****************************************************************/
/* ImageLibIterateImages*/
/**
 * @brief Creates an iterator for working with a collection of images in the database.
 *
 * Creates an iterator for working with a collection of images in the database.
 * When finished, the iterator refers to a data structure that contains images
 * The iterator can be used to step through images, draw images, sort images, and search for
 * images by name.
 *
 * @param   libRef              IN  Library reference number.
 * @param   category            IN  The category to search. Pass 0 for unfiled. Pass dmAllCategories to iterate through all images in the databse.
 * @param   sortType            IN  Initial sort order of the datastructure (kNoSortOrder, kSortByName, or kSortByDate)
 * @param   imageCountP         OUT Number of images in the iterator data structure. Pass NULL if you don't care about this value.
 * @param   errP                OUT 0 on success, non-zero on error. This parameter should not be null.
 * @retval  ImageIteratorHandle Opaque iterator handle.
 *
 * @note The returned iterator handle can be passed to other iterator routines
 * that take an iterator handle. The handle should be freed by calling
 * ImageLibIterFree.
 *
 * @see ImageLibIterFree
 * @author Harold Howe
 *
 ****************************************************************/
ImageIteratorHandle ImageLibIterateImages(UInt16 libRef,
                                          UInt16 category,
                                          UInt16 sortType,
                                          UInt16 *imageCountP,
                                          Err *errP)
    SYS_TRAP(kImageLibTrapIterateImages);

/****************************************************************/
/* ImageLibIterateVFSImages*/
/**
 * @brief Creates an iterator for working with a collection of images on a
 * VFS volume.
 *
 * Creates an iterator for working with a collection of images on a
 * VFS volume. When finished, the iterator refers to a data structure that
 * contains images. The iterator can be used to step through images, draw
 * images, sort images, and search for images by name.
 *
 * @param   libRef              IN  Library reference number.
 * @param   volRefNum           IN  VFS volume to search.
 * @param   path                IN  Directory to start searching in.
 * @param   recurseBelow        IN  true to recurse in all subdirectories of path. false to search in path only.
 * @param   sortType            IN  Initial sort order of the datastructure (kNoSortOrder, kSortByName, or kSortByDate)
 * @param   imageCountP         OUT Number of images in the iterator data structure. Pass NULL if you don't care about this value.
 * @param   errP                OUT 0 on success, non-zero on error. This parameter should not be null.
 * @retval  ImageIteratorHandle Opaque iterator handle.
 *
 * @note The returned iterator handle can be passed to other iterator routines
 * that take an iterator handle. The handle should be freed by calling
 * ImageLibIterFree.
 *
 * @see ImageLibIterFree
 * @author Harold Howe
 *
 ****************************************************************/
ImageIteratorHandle ImageLibIterateVFSImages(UInt16 libRef,
                                             UInt16 volRefNum,
                                             const char *path,
                                             Boolean recurseBelow,
                                             UInt16 sortType,
                                             UInt16 *imageCount, Err *errP)
    SYS_TRAP(kImageLibTrapIterateVFSImages)  ;


/****************************************************************/
/* ImageLibIterSort*/
/**
 * @brief Sorts the images in an iterator chain.
 *
 * Sorts the images in an iterator chain. Note that this only reorganizes images
 * in the iterator data structure. This does not alter the way images are stored
 * in the database or on a card.
 * images, sort images, and search for images by name.
 *
 * @param   libRef              IN  Library reference number.
 * @param   iter                IN  Handle to an iterator.
 * @param   sortType            IN  New sort order of the datastructure (kNoSortOrder, kSortByName, kSortByDate, kSortByNameDesc, or kSortByDateDesc)
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note The iterator handle should be created with ImageLibIterateImages or
 * ImageLibIterateVFSImages.
 *
 * @see ImageLibIterateImages
 * @see ImageLibIterateVFSImages
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibIterSort (UInt16 libRef,ImageIteratorHandle iter, UInt16 sortType )
    SYS_TRAP(kImageLibTrapIterSort);

/****************************************************************/
/* ImageLibIterGetImageInfo*/
/**
 * @brief Retrieves information about a single image in an iterator chain.
 *
 * @param   libRef              IN  Library reference number.
 * @param   iter                IN  Handle to an iterator.
 * @param   index               IN  Index of the image in the iterator. [0,imageCount)
 * @param   name                OUT Buffer to receive the name of the image. For VFS images, this is the full path and filename of the image (ie "/dcim/picture001.jpg"). For internal images, this is the name of the picture (ie "Picture001")
 * @param   nameLen             IN  Size in bytes of the name buffer.
 * @param   categoryP           OUT Category of the picture if it is stored in the image database. 0xFF if it is a VFS picture.
 * @param   recIndexP           OUT Record index of the picture if it is stored in the image database. kInvalidRecIndex if it is a VFS picture.
 * @param   volRefNumP          OUT VFS volume ref number of the picture if it is stored on a VFS volume. vfsInvalidVolRef if it is stored in the internal database.
 * @param   createdP            OUT Timestamp when picture was creatd. Pass NULL for this parameter if you don't want to retrieve it.
 * @param   sizeP               OUT Size of the image data in bytes. Pass NULL for this parameter if you don't want to retrieve it.
 * @param   path                OUT Directory that the picture is stored in if it is a VFS image (ie /DCIM). Empty string if it is an internal image.
 * @param   pathLen             IN  Size in bytes of the path buffer.
 * @param   lockedP             OUT true if the image is locked. False otherwise. VFS images are never locked.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note The iterator handle should be created with ImageLibIterateImages or
 * ImageLibIterateVFSImages.
 *
 * @note Pass NULL for any OUT parameter that you don't care about.
 *
 * @see ImageLibIterateImages
 * @see ImageLibIterateVFSImages
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibIterGetImageInfo(UInt16 libRef, ImageIteratorHandle iter,
                             UInt16 index, char *name, UInt16 nameLen,
                             UInt16 *categoryP, UInt16 *recIndexP,
                             UInt16 *volRefNumP, UInt32* createdP,
                             UInt32* sizeP, char *path, UInt16 pathLen,
                             Boolean *lockedP)
    SYS_TRAP(kImageLibTrapIterGetImageInfo)  ;


/****************************************************************/
/* ImagelibIterGetCount*/
/**
 * @brief Retrieves the number of images stored in the iterator data structure.
 *
 * @param   libRef              IN  Library reference number.
 * @param   iter                IN  Handle to an iterator.
 * @param   imageCountP         OUT Number of images in the iterator data structure.
 * @retval  Err                 0 on success, non-zero on error.
 *
 * @note The iterator handle should be created with ImageLibIterateImages or
 * ImageLibIterateVFSImages.
 *
 * @note Iterator routines that take an index should ensure that the index is
 * less than the value returned in imageCountP.
 *
 * @see ImageLibIterateImages
 * @see ImageLibIterateVFSImages
 * @author Harold Howe
 *
 ****************************************************************/
Err ImagelibIterGetCount(UInt16 libRef, ImageIteratorHandle iter,
                         UInt16 *imageCountP)
    SYS_TRAP(kImagelibTrapIterGetCount) ;

/****************************************************************/
/* ImageLibIterDeleteImage*/
/**
 * @brief Deletes an image (either from the database or from a VFS volume)
 *
 * Permanently deletes an image given a reference to the image in an iterator.
 * Given an iterator and an index to an image in the iterator, this routine
 * determines whether the image resides in the internal database or on a VFS
 * volume. If it resides on a VFS volume, the routine attempts to delete it by
 * calling VFSFileDelete. If it is an internal image, the picture is nuked by
 * calling ImageLibDeleteImage. After the image is deleted, it is removed from
 * the iterator chain. All subsequent images in the iterator data structure move
 * down one spot. The count of images in the iterator chain is decremented by
 * one.
 *
 * @param   libRef  IN  Library reference number.
 * @param   iter    IN  Handle to an iterator.
 * @param   index   IN  Index of the image to delete. This is an index into the iterator, not an index to the image database.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @note The iterator handle should be created with ImageLibIterateImages or
 * ImageLibIterateVFSImages.
 *
 * @note Deleting an image invalidates the iterator index for all subsequent
 * images in the iterator chain. If you need to delete a range of images in an
 * iterator, it is best to loop from back to front.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibIterDeleteImage(UInt16 libRef,ImageIteratorHandle iter,
                            UInt16 index)
    SYS_TRAP(kImageLibTrapIterDeleteImage) ;

/****************************************************************/
/* ImageLibIterRemoveImage*/
/**
 * @brief Removes an image from an iterator chain without deleting it from its
 * original location.
 *
 * Removes an image from an iterator chain without deleting it from its
 * original location. Once an image is removed, it can no longer be accessed via
 * the iterator. However, the image is still accessible from its original location
 * (either in the image database or on a VFS card).
 *
 * @param   libRef  IN  Library reference number.
 * @param   iter    IN  Handle to an iterator.
 * @param   index   IN  Index of the image to remove. This is an index into the iterator, not an index to the image database.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @note The iterator handle should be created with ImageLibIterateImages or
 * ImageLibIterateVFSImages.
 *
 * @note Removing an image invalidates the iterator index for all subsequent
 * images in the iterator chain. If you need to remove a range of images in an
 * iterator, it is best to loop from back to front.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibIterRemoveImage(UInt16 libRef, ImageIteratorHandle iter,
                            UInt16 index)
     SYS_TRAP(kImageLibTrapIterRemoveImage) ;


/****************************************************************/
/* ImageLibIterFree*/
/**
 * @brief Frees the memory associated with an iterator chain.
 *
 *
 * @param   libRef  IN  Library reference number.
 * @param   iter    IN  Handle to an iterator.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @note The iterator handle should be created with ImageLibIterateImages or
 * ImageLibIterateVFSImages.
 *
 * @note Once the iterator has been freed, it should not be used anymore.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibIterFree (UInt16 libRef, ImageIteratorHandle iter)
    SYS_TRAP(kImageLibTrapIterFree);


/****************************************************************/
/* ImageLibIterDrawImage*/
/**
 * @brief Draws an image in an iterator chain to the current draw window.
 *
 * Draws an image in an iterator chain to the current draw window at x,y.
 * x and y are window relative coordinates.
 *
 * @param   libRef  IN  Library reference number.
 * @param   iter    IN  Handle to an iterator.
 * @param   index   IN  Index of the image to draw. This is an index into the iterator, not an index to the image database.
 * @param   x       IN  x location to draw the preview image, relative to the current draw window.
 * @param   y       IN  y location to draw the preview image, relative to the current draw window.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @note If the image resides in the internal database, this routine calls
 * ImageLibImageDraw to draw it. If it is a VFS image the call is dispatched to
 * ImageLibImageDrawFromVFS
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibIterDrawImage(UInt16 libRef, ImageIteratorHandle iter,
                          UInt16 index, Coord x, Coord y)
    SYS_TRAP(kImageLibTrapIterDrawImage);


/****************************************************************/
/* ImageLibIterDrawThumbnail*/
/**
 * @brief Draws a thumbnail for an image in an iterator chain to the current
 * draw window.
 *
 * Draws a thumbnail for an image in an iterator chain to the current draw
 * window at x,y. x and y are window relative coordinates.
 *
 * @param   libRef  IN  Library reference number.
 * @param   iter    IN  Handle to an iterator.
 * @param   index   IN  Index of the image to draw. This is an index into the iterator, not an index to the image database.
 * @param   x       IN  x location to draw the preview image, relative to the current draw window.
 * @param   y       IN  y location to draw the preview image, relative to the current draw window.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @note If the image resides in the internal database, this routine calls
 * ImageLibThumbnailDraw to draw it. If it is a VFS image the call is dispatched to
 * ImageLibThumbnailDrawFromVFS
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibIterDrawThumbnail (UInt16 libRef, ImageIteratorHandle iter,
                               UInt16 index, Coord x, Coord y)
    SYS_TRAP(kImageLibTrapIterDrawThumbnail);

/****************************************************************/
/* ImageLibIterSearch*/
/**
 * @brief Searches for an image in an iterator chain by name
 *
 * Searches for an image in an iterator chain by name. To match, a picture's
 * name must the name string starting in the first character. If partical match
 * is true, then the entire string must match. Case is ignored for all
 * comparisons

 *
 * @param   libRef       IN  Library reference number.
 * @param   iter         IN  Handle to an iterator.
 * @param   name         IN  String to search for.
 * @param   partialMatch IN  If true, only the beginning of a picture name must match. If false, the entire name must match.
 * @param   index        OUT Contains the index of the first picture that matches the search string. kInvalidRecIndex if no match found.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @note Pattern matching and wildcards are not supported. 
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibIterSearch(UInt16 libRef, ImageIteratorHandle iterH,
                       const char *name, Boolean partialMatch,
                       UInt16 *index)
    SYS_TRAP(kImageLibTrapIterSearch);

/****************************************************************/
/* ImageLibSetProgressCallback*/
/**
 * @brief Sets a progress callback function.
 *
 * Sets a progress callback function. The image library will invoke this routine
 * periodically during long processing, such as compressing or decompressing a
 * jpeg or resizing an image.
 *
 * @param   libRef       IN  Library reference number.
 * @param   callback     IN  Address of the callback function. Pass NULL to reset the callback to nothing.
 * @retval  void
 *
 * @note The callback function should have the following signature
 *
 * @code void callback(Int32 progress, Int32 max, Int8 operation); \
 *
 * @note max is the total number of operations that must be performed. For a JPEG
 * compression or decompression, this equates to the number of horizontal
 * scan lines in the image. The progress value will range from 0 to max.
 * The imaging library will invoked the callback repeatedly. On each pass, the
 * progress variable will increase by some unspecified amount. The operation
 * argument determines the type of operation being performed. Possible values
 * are kResizeOperation, kJPEGOperation, and kVFSOperation.
 *
 * @note All of the APIs that decompress or resize images use the callback
 * mechanism. ImageLibImageSave also invokes it.

 *
 * @author Harold Howe
 *
 ****************************************************************/
void ImageLibSetProgressCallback(UInt16 libRef,
                                 ImageLibProgressCallbackType callback)
    SYS_TRAP(kImageLibTrapSetProgressCallback);


/****************************************************************/
/* ImageLibCopyImage*/
/**
 * @brief Creates a copy of an image in the database.
 *
 * @param   libRef       IN  Library reference number.
 * @param   recIndex     IN  Index of the image to copy.
 * @param   newName      IN  Name of the newly copied image.
 * @param   newRecIndexP OUT Index of the newly copied image. Pass NULL if you don't care about this value.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibCopyImage(UInt16 libRef, UInt16 recIndex,
                      const char *newName, UInt16 *newRecIndexP)
    SYS_TRAP(kImageLibTrapCopyImage);


/****************************************************************/
/* ImageLibFindImageByID*/
/**
 * @brief Determines the record index of an image in the database given a unique ID.
 *
 * Determines the record index of an image in the database given a unique ID.
 * The image is found by calling DmFindRecordByID on the main database.
 *
 * @param   libRef       IN  Library reference number.
 * @param   uniqueID     IN  Unique ID of the image to find.
 * @param   recIndexP    OUT Record index of the image.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @note If you need to store a permanent reference to a picture in the
 * database, it is best to store its unique ID. You can obtain the unique ID
 * of an image by calling ImageLibGetImageInfo. To access an image by unique
 * ID, call ImageLibFindImageByID to retrieve the record index, and then use
 * the record index to access the picture.
 *
 * @see ImageLibGetImageInfo
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibFindImageByID (UInt16 libRef, UInt32 uniqueID, UInt16 *recIndexP)
    SYS_TRAP(kImageLibTrapFindImageByID);


/****************************************************************/
/* ImageLibPreviewStart*/
/**
 * @brief Turns on the direct draw preview mode of the camera.
 *
 * This routine serves as a front end to the camera driver's
 * CameraLibPreviewStart function. After being called, the camera will display
 * preview images to the supplied window at the given coordinates.
 *
 * @param   libRef       IN  Library reference number.
 * @param   windowH      IN  Window handle where preview images should be drawn. This should generally be a screen window.
 * @param   x            IN  x location to draw the preview image. Relative to windowH.
 * @param   y            IN  y location to draw the preview image. Relative to windowH.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @see ImageLibPreviewStop
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibPreviewStart (UInt16 libRef, void * windowH, Coord x, Coord y)
    SYS_TRAP(kImageLibTrapPreviewStart);

/****************************************************************/
/* ImageLibPreviewStop*/
/**
 * @brief Turns off the direct draw preview mode of the camera.
 *
 * This routine serves as a front end to the camera driver's
 * CameraLibPreviewStop function. It halts previews that were initiated by a
 * call to ImageLibPreviewStart.
 *
 * @param   libRef       IN  Library reference number.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @see ImageLibPreviewStart
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibPreviewStop  (UInt16 libRef)
    SYS_TRAP(kImageLibTrapPreviewStop);

/****************************************************************/
/* ImageLibDrawJPEG*/
/**
 * @brief Decompresses a blob of JPEG data and draws it to the current draw window.
 *
 * Decompresses a blob of JPEG data and draws it to the current draw window.
 * The picture is drawn at left,top, which are relative to the draw window.
 *
 * @param   libRef       IN  Library reference number.
 * @param   jpegDataP    IN  Pointer to a JPEG image in memory.
 * @param   jpegSize     IN  Size of the source image in bytes.
 * @param   left         IN  x location to draw the image, relative to the current draw window.
 * @param   top          IN  y location to draw the image, relative to the current draw window.
 * @param   fitToScreen  IN  If true, the JPEG is resized to fit in a box defined by width and height. If false, image is not resized.
 * @param   width        IN  Max width of drawn image. Ignored if fitToScreen is false.
 * @param   height       IN  Max height of drawn image. Ignored if fitToScreen is false.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @note If the image needs to be resized, its aspect ratio is maintained. To
 * determine how an image will be resized beforehand, call
 * ImageLibGetDimensionsJPEG.
 *
 * @see ImageLibGetDimensionsJPEG
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibDrawJPEG(UInt16 libRef, MemPtr jpegDataP, UInt32 jpegSize,
                     Coord left, Coord top, Boolean fitToScreen,
                     Coord width, Coord height)
    SYS_TRAP(kImageLibTrapDrawJPEG);

/****************************************************************/
/* ImageLibTurnCameraOff*/
/**
 * @brief Deactivates the camera hardware by unloading the camera driver.
 *
 * @param   libRef       IN  Library reference number.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibTurnCameraOff(UInt16 libRef)
    SYS_TRAP(kImageLibTrapTurnCameraOff);

/****************************************************************/
/* ImageLibSetImageID*/
/**
 * @brief Sets the media and container IDs for an image in the database.
 *
 * @param   libRef       IN  Library reference number.
 * @param   recIndex     IN  Index of image.
 * @param   mediaIDP     IN  Media ID.
 * @param   containderIDP IN Container ID.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @note The media ID and container ID should both be 21 bytes in size. The image
 * library copies 21 bytes from the supplied buffers into the main record for the
 * image.
 *
 * @see ImageLibGetImageID
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibSetImageID(UInt16 libRef, UInt16 recIndex,
                      const char* mediaIDP, const char *containerIDP)
    SYS_TRAP(kImageLibTrapSetImageID);

/****************************************************************/
/* ImageLibGetImageID*/
/**
 * @brief Gets the media and container IDs for an image in the database.
 *
 * @param   libRef       IN  Library reference number.
 * @param   recIndex     IN  Index of image.
 * @param   mediaIDP     IN  Media ID.
 * @param   containderIDP IN Container ID.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @note The media ID and container ID should both be at least 21 bytes in size.
 * The library copies 21 bytes to the supplied buffers.
 *
 * @see ImageLibSetImageID
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibGetImageID(UInt16 libRef, UInt16 recIndex,
                      char* mediaIDP, char *containerIDP)
    SYS_TRAP(kImageLibTrapGetImageID);

/****************************************************************/
/* ImageLibGetDimensions*/
/**
 * @brief Retrieves the dimensions of an image in the database.
 *
 * This routine allows clients of the library to query the dimensions of an image
 * in the database. If fitToDimensions is false, the routine copies the full
 * dimensions of the image to widthP and heightP. The initial values of widthP
 * and heightP are ignored. If fitToDimensions is true, the routine calculates
 * how big the image will be after it is downsized to fit in a box determined
 * by the initial values of widthP and heightP.
 *
 * @param   libRef       IN  Library reference number.
 * @param   recIndex     IN  Index of image.
 * @param   widthP       IN/OUT On output, contains the width of the image. On input, if fitToDimensions is true, determines the max width that the image should be.
 * @param   heightP      IN/OUT On output, contains the height of the image. On input, if fitToDimensions is true, determines the max height that the image should be.
 * @param   fitToDimensions  IN If true, tells the library to return the dimensions that an image would be if it was forced to draw in a box bounded by widthP and heightP.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibGetDimensions     (UInt16 libRef, UInt16 recIndex,
                               Coord *width, Coord *height,
                               Boolean fitToDimensions)
    SYS_TRAP(kImageLibTrapGetDimensions    );


/****************************************************************/
/* ImageLibGetDimensionsVFS*/
/**
 * @brief Retrieves the dimensions of an image on a VFS volume.
 *
 * This routine allows clients of the library to query the dimensions of an image
 * that resides on a VFS volume. The routine follows the same semantics as
 * ImageLibGetDimensions.
 *
 * @param   libRef       IN  Library reference number.
 * @param   volRefNum    IN  Ref number of the VFS volume
 * @param   fileName     IN  Filename of the image (ie "/DCIM/picture.jpg")
 * @param   widthP       IN/OUT On output, contains the width of the image. On input, if fitToDimensions is true, determines the max width that the image should be.
 * @param   heightP      IN/OUT On output, contains the height of the image. On input, if fitToDimensions is true, determines the max height that the image should be.
 * @param   fitToDimensions  IN If true, tells the library to return the dimensions that an image would be if it was forced to draw in a box bounded by widthP and heightP.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @see ImageLibGetDimensions
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibGetDimensionsVFS  (UInt16 libRef, UInt16 volRefNum,
                               const char* fileName,  Coord *width,
                               Coord *height, Boolean fitToDimensions)
    SYS_TRAP(kImageLibTrapGetDimensionsVFS );


/****************************************************************/
/* ImageLibIterGetDimensions*/
/**
 * @brief Retrieves the dimensions of an image in an iterator chain.
 *
 * This routine allows clients of the library to query the dimensions of an image
 * in an iterator chain. The routine follows the same semantics as
 * ImageLibGetDimensions.
 *
 * @param   libRef       IN  Library reference number.
 * @param   iter         IN  Iterator handle
 * @param   index        IN  Index of the image in the iterator. [0,imageCount)
 * @param   widthP       IN/OUT On output, contains the width of the image. On input, if fitToDimensions is true, determines the max width that the image should be.
 * @param   heightP      IN/OUT On output, contains the height of the image. On input, if fitToDimensions is true, determines the max height that the image should be.
 * @param   fitToDimensions  IN If true, tells the library to return the dimensions that an image would be if it was forced to draw in a box bounded by widthP and heightP.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @see ImageLibGetDimensions
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibIterGetDimensions (UInt16 libRef, ImageIteratorHandle iter,
                               UInt16 index, Coord *width, Coord *height,
                               Boolean fitToDimensions)
    SYS_TRAP(kImageLibTrapIterGetDimensions);


/****************************************************************/
/* ImageLibGetDimensionsJPEG*/
/**
 * @brief Retrieves the dimensions of a blob of JPEG data in memory.
 *
 * This routine allows clients of the library to query the dimensions of an
 * arbitrary blob of JPEG data. The routine follows the same semantics as
 * ImageLibGetDimensions.
 *
 * @param   libRef       IN  Library reference number.
 * @param   jpegDataP    IN  Pointer to a JPEG image in memory.
 * @param   jpegSize     IN  Size of the source image in bytes.
 * @param   widthP       IN/OUT On output, contains the width of the image. On input, if fitToDimensions is true, determines the max width that the image should be.
 * @param   heightP      IN/OUT On output, contains the height of the image. On input, if fitToDimensions is true, determines the max height that the image should be.
 * @param   fitToDimensions  IN If true, tells the library to return the dimensions that an image would be if it was forced to draw in a box bounded by widthP and heightP.
 * @retval  Err     0 on success, non-zero on error.
 *               \
 * @see ImageLibGetDimensions
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibGetDimensionsJPEG (UInt16 libRef, MemPtr jpegDataP, UInt32 jpegSize,
                               Coord *width, Coord *height,
                               Boolean fitToDimensions)
    SYS_TRAP(kImageLibTrapGetDimensionsJPEG);


/****************************************************************/
/* ImageLibResize*/
/**
 * @brief Resizes an image in the database to any arbitrary size.
 *
 * This routine resizes an image in the database to any size. The routine
 * can maintain the existing aspect ratio of the image, or it can stretch it
 * to fit any size.
 *
 * @param   libRef       IN  Library reference number.
 * @param   recIndex     IN  Index of image.
 * @param   widthP       IN/OUT On output, contains the new width of the image. On input, if maintainAspectRatio is true, determines the max width that the image should be. If maintainAspectRatio is false, determines the exact width that the image should be after resizing.
 * @param   heightP      IN/OUT On output, contains the new width of the image. On input, if maintainAspectRatio is true, determines the max width that the image should be. If maintainAspectRatio is false, determines the exact width that the image should be after resizing.
 * @param   maintainAspectRatio  IN If true, tells the library to maintain the aspect ratio of the image. In this case, the input values of widthP and heightP serve as maximum guidelines. If false, the image is stretched to fit the input values of widthP and heightP. the dimensions that an image would be if it was forced to draw in a box bounded by widthP and heightP.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibResize (UInt16 libRef, UInt16 recIndex,
                    Coord *widthP, Coord *heightP, Boolean maintainAspectRatio)
    SYS_TRAP(kImageLibTrapResize     );

/****************************************************************/
/* ImageLibResizeVFS*/
/**
 * @brief Resizes an image on a VFS volume to any arbitrary size.
 *
 * This routine resizes a VFS image to any size. The routine follows the same
 * semantics as ImageLibResize.
 *
 * @param   libRef       IN  Library reference number.
 * @param   volRefNum    IN  Ref number of the VFS volume
 * @param   fileName     IN  Filename of the image (ie "/DCIM/picture.jpg")
 * @param   widthP       IN/OUT On output, contains the new width of the image. On input, if maintainAspectRatio is true, determines the max width that the image should be. If maintainAspectRatio is false, determines the exact width that the image should be after resizing.
 * @param   heightP      IN/OUT On output, contains the new width of the image. On input, if maintainAspectRatio is true, determines the max width that the image should be. If maintainAspectRatio is false, determines the exact width that the image should be after resizing.
 * @param   maintainAspectRatio  IN If true, tells the library to maintain the aspect ratio of the image. In this case, the input values of widthP and heightP serve as maximum guidelines. If false, the image is stretched to fit the input values of widthP and heightP. the dimensions that an image would be if it was forced to draw in a box bounded by widthP and heightP.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @see ImageLibResize
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibResizeVFS(UInt16 libRef, UInt16 volRefNum, const char* fileName,
                      Coord *widthP, Coord *heightP,
                      Boolean maintainAspectRatio)
    SYS_TRAP(kImageLibTrapResizeVFS  );


Err ImageLibIterResize (UInt16 libRef, ImageIteratorHandle iter, UInt16 index, Coord *widthP, Coord *heightP, Boolean maintainAspectRatio) SYS_TRAP(kImageLibTrapIterResize );


/****************************************************************/
/* ImageLibIterResize*/
/**
 * @brief Resizes an image in an iterator chain.
 *
 * This routine resizes an image in an iterator chain to any size. The routine
 * follows the same semantics as ImageLibResize.
 *
 * @param   libRef       IN  Library reference number.
 * @param   iter         IN  Iterator handle
 * @param   index        IN  Index of the image in the iterator. [0,imageCount)
 * @param   widthP       IN/OUT On output, contains the new width of the image. On input, if maintainAspectRatio is true, determines the max width that the image should be. If maintainAspectRatio is false, determines the exact width that the image should be after resizing.
 * @param   heightP      IN/OUT On output, contains the new width of the image. On input, if maintainAspectRatio is true, determines the max width that the image should be. If maintainAspectRatio is false, determines the exact width that the image should be after resizing.
 * @param   maintainAspectRatio  IN If true, tells the library to maintain the aspect ratio of the image. In this case, the input values of widthP and heightP serve as maximum guidelines. If false, the image is stretched to fit the input values of widthP and heightP. the dimensions that an image would be if it was forced to draw in a box bounded by widthP and heightP.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @see ImageLibResize
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibIterResize (UInt16 libRef, ImageIteratorHandle iter, UInt16 index,
                        Coord *widthP, Coord *heightP,
                        Boolean maintainAspectRatio)
    SYS_TRAP(kImageLibTrapIterResize );



/****************************************************************/
/* ImageLibResizeJPEG*/
/**
 * @brief Resizes a JPEG in memory.
 *
 * This routine resizes a JPEG in memory to any size. The routine
 * follows the same semantics as ImageLibResize, except that it creates a new
 * JPEG in memory as a result.
 *
 * @param   libRef       IN  Library reference number.
 * @param   jpegInputP   IN  Pointer to a JPEG image in memory.
 * @param   inputSize    IN  Size of the source image in bytes.
 * @param   widthP       IN/OUT On output, contains the new width of the image. On input, if maintainAspectRatio is true, determines the max width that the image should be. If maintainAspectRatio is false, determines the exact width that the image should be after resizing.
 * @param   heightP      IN/OUT On output, contains the new width of the image. On input, if maintainAspectRatio is true, determines the max width that the image should be. If maintainAspectRatio is false, determines the exact width that the image should be after resizing.
 * @param   maintainAspectRatio  IN If true, tells the library to maintain the aspect ratio of the image. In this case, the input values of widthP and heightP serve as maximum guidelines. If false, the image is stretched to fit the input values of widthP and heightP. the dimensions that an image would be if it was forced to draw in a box bounded by widthP and heightP.
 * @param   outputPP     OUT Pointer to the newly sized JPEG. The caller is responsible for freeing this memory.
 * @param   outputSizeP  OUT Size in bytes of the newly sized JPEG.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @see ImageLibResize
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibResizeJPEG (UInt16 libRef, MemPtr jpegInputP, UInt32 inputSize,
                        Coord *widthP, Coord *heightP,
                        Boolean maintainAspectRatio, MemPtr *outputPP,
                        UInt32 *outputSizeP)
    SYS_TRAP(kImageLibTrapResizeJPEG);



/****************************************************************/
/* ImageLibIterRefresh*/
/**
 * @brief Refreshes the information for an image in an iterator chain.
 *
 * Refreshes the information for an image in an iterator chain. If the image is
 * stored in the image database, this routine updates the name, recIndex,
 * category, size, timestamp, and locked status of the image. If it is a VFS
 * picture, this routine updates the timestamp and size of the picture.
 *
 * @param   libRef       IN  Library reference number.
 * @param   iter         IN  Handle to an iterator.
 * @param   index        IN  Index of the image in the iterator. [0,imageCount)
 * @param   newVFSName   IN  If picture is a VFS file, pass its new name for this parameters
 * @retval  Err     0 on success, non-zero on error.
 *
 * @note Call this function when an iterator refers to an image that has changed
 * since the iterator was created. For example, if you downsize or resize an
 * iternal image, call ImageLibIterRefresh to update the iterator information
 * for that image.
 *
 * @note If you rename a VFS picture that is referenced by an iterator chain, you
 * can pass its new name for the newVFSName argument. Pass the full path and
 * filename of the image. If you pass a string for this argument, the name of
 * file in the iterator chain will be updated. Pass NULL for the newVFSName
 * parameter if the iterator image refers to an internal picture or a VFS
 * picture that whose name has not been changed (If you don't know what this is
 * about, pass NULL).
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibIterRefresh(UInt16 libRef, ImageIteratorHandle iter, UInt16 index,
                        const char *newVFSName)
    SYS_TRAP(kImageLibTrapIterRefresh);

/****************************************************************/
/* ImageLibSetJPEGQuality*/
/**
 * @brief Sets the compression factor for all JPEG compression operations.
 *
 * Sets the compression factor for all JPEG compression operations performed
 * by the imaging library. The compression factor shoule be a value in the range
 * of 1-99.
 *
 * @param   libRef       IN  Library reference number.
 * @param   quality      IN  new compression quality.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibSetJPEGQuality(UInt16 libRef, Int32 value)
    SYS_TRAP(kImageLibTrapSetJPEGQuality);

/****************************************************************/
/* ImageLibGetJPEGQuality*/
/**
 * @brief Returns the compression factor used for JPEG compression operations.
 *
 *
 * @param   libRef       IN  Library reference number.
 * @retval  Int32      Compression value. [1,99]
 *
 * @author Harold Howe
 *
 ****************************************************************/
Int32 ImageLibGetJPEGQuality(UInt16 libRef)
    SYS_TRAP(kImageLibTrapGetJPEGQuality);



/****************************************************************/
/* ImageLibLockImage*/
/**
 * @brief Returns the compression factor used for JPEG compression operations.
 *
 *
 * @param   libRef              IN   Library reference number.
 * @param   recIndex            IN   Index of the image to compress.
 * @retval  Err     0 on success, non-zero on error.
 *
 * @note Once an image is locked, it is locked forever and can't be unlocked.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Err ImageLibLockImage(UInt16 libRef, UInt16 recIndex)
    SYS_TRAP(kImageLibTrapLockImage);


/****************************************************************/
/* ImageLibGetAveragePictureSize*/
/**
 * @brief Returns the average size that a picture will be at the current compression factor.
 *
 *
 * @param   libRef        IN   Library reference number.
 * @param   fullsize      IN   True to return average of last 20 fullsize captures. False to return average of palm size captures.
 * @retval  Int32    0 Average size.
 *
 * @author Harold Howe
 *
 ****************************************************************/
Int32 ImageLibGetAveragePictureSize(UInt16 libRef, Boolean fullsize)
    SYS_TRAP(kImageLibTrapGetAveragePictureSize);


/****************************************************************/
/* ImageLibCheckLockedImages*/
/**
 * @brief Verifies the locked images match the given phone number. If they don't, all locked images
 * are purged from the database. 
 *
 *
 * @param   libRef        IN   Library reference number.
 * @param   phoneNumber   IN   String containing the phone number to verify against.
 *
 * @author Harold Howe
 *
 ****************************************************************/
void ImageLibCheckLockedImages(UInt16 libRef, const Char *phoneNumber)
    SYS_TRAP(kImageLibTrapCheckLockedImages);


#ifdef __cplusplus
}
#endif


#endif
