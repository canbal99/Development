/*
 * Copyright (c) 2016 Razeware LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

import Foundation

// Notification when new photo instances are added
let photoManagerContentAddedNotification = "com.raywenderlich.GooglyPuff.PhotoManagerContentAdded"
// Notification when content updates (i.e. Download finishes)
let photoManagerContentUpdatedNotification = "com.raywenderlich.GooglyPuff.PhotoManagerContentUpdated"

// Photo Credit: Devin Begley, http://www.devinbegley.com/
let overlyAttachedGirlfriendURLString = "http://i.imgur.com/UvqEgCv.png"
let successKidURLString = "http://i.imgur.com/dZ5wRtb.png"
let lotsOfFacesURLString = "http://i.imgur.com/tPzTg7A.jpg"

typealias PhotoProcessingProgressClosure = (_ completionPercentage: CGFloat) -> Void
typealias BatchPhotoDownloadingCompletionClosure = (_ error: NSError?) -> Void

private let _sharedManager = PhotoManager()

class PhotoManager {
  class var sharedManager: PhotoManager {
    return _sharedManager
  }

  fileprivate let concurrentPhotoQueue = DispatchQueue( label: "com.raywenderlich.GooglyPuff.photoQueue", attributes: .concurrent)
  
  fileprivate var _photos: [Photo] = []
  var photos: [Photo] {
    var photosCopy: [Photo]!
    concurrentPhotoQueue.sync { // 1
        photosCopy = self._photos // 2
    }
    return photosCopy
  }
  
  func addPhoto(_ photo: Photo) {
    concurrentPhotoQueue.async(flags: .barrier) { // 1
      self._photos.append(photo)
      DispatchQueue.main.async {
        self.postContentAddedNotification()
      }
    }
  }
    
    func downloadPhotosWithCompletion_old01(_ completion: BatchPhotoDownloadingCompletionClosure?) {
        DispatchQueue.global(qos: .userInitiated).async { // 1
        var storedError: NSError?
        let downloadGroup = DispatchGroup() // 2
        for address in [overlyAttachedGirlfriendURLString,
                        successKidURLString,
                        lotsOfFacesURLString] {
                            let url = URL(string: address)
                            downloadGroup.enter() // 3
                            let photo = DownloadPhoto(url: url!) {
                                _, error in
                                if error != nil {
                                    storedError = error
                                }
                                downloadGroup.leave() // 4
                            }
                            PhotoManager.sharedManager.addPhoto(photo)
        }
        
        downloadGroup.wait() //
        DispatchQueue.main.async { // 6
          completion?(storedError)
          }
        }
    }
    
    func downloadPhotosWithCompletion_old02(_ completion: BatchPhotoDownloadingCompletionClosure?) {
        var storedError: NSError?
        let downloadGroup = DispatchGroup() // 2
        for address in [overlyAttachedGirlfriendURLString,
                        successKidURLString,
                        lotsOfFacesURLString] {
                            let url = URL(string: address)
                            downloadGroup.enter() // 3
                            let photo = DownloadPhoto(url: url!) {
                                _, error in
                                if error != nil {
                                    storedError = error
                                }
                                downloadGroup.leave() // 4
                            }
                            PhotoManager.sharedManager.addPhoto(photo)
        }
        
        downloadGroup.notify(queue: DispatchQueue.main) { // 2
            completion?(storedError)
        }
    }
    
    func downloadPhotosWithCompletion_old03(_ completion: BatchPhotoDownloadingCompletionClosure?) {
        var storedError: NSError?
        let downloadGroup = DispatchGroup()
        let addresses = [overlyAttachedGirlfriendURLString,
                         successKidURLString,
                         lotsOfFacesURLString]
        let _ = DispatchQueue.global(qos: .userInitiated)
        DispatchQueue.concurrentPerform(iterations: addresses.count) {
            i in
            let index = Int(i)
            let address = addresses[index]
            let url = URL(string: address)
            downloadGroup.enter()
            let photo = DownloadPhoto(url: url!) {
                _, error in
                if error != nil {
                    storedError = error
                }
                downloadGroup.leave()
            }
            PhotoManager.sharedManager.addPhoto(photo)
        }
        downloadGroup.notify(queue: DispatchQueue.main) {
            completion?(storedError)
        }
    }
    
    func downloadPhotosWithCompletion(_ completion: BatchPhotoDownloadingCompletionClosure?) {
        var storedError: NSError?
        let downloadGroup = DispatchGroup()
        var addresses = [overlyAttachedGirlfriendURLString,
                         successKidURLString,
                         lotsOfFacesURLString]
        addresses += addresses + addresses // 1
        var blocks: [DispatchWorkItem] = [] // 2
        
        for i in 0 ..< addresses.count {
            downloadGroup.enter()
            let block = DispatchWorkItem(flags: .inheritQoS) { // 3
                let index = Int(i)
                let address = addresses[index]
                let url = URL(string: address)
                let photo = DownloadPhoto(url: url!) {
                    _, error in
                    if error != nil {
                        storedError = error
                    }
                    downloadGroup.leave()
                }
                PhotoManager.sharedManager.addPhoto(photo)
            }
            blocks.append(block)
            DispatchQueue.main.async(execute: block) // 4
        }
        
        for block in blocks[3 ..< blocks.count] { // 5
            let cancel = arc4random_uniform(2) // 6
            if cancel == 1 {
                block.cancel() // 7
                downloadGroup.leave() // 8
            }
        }
        
        downloadGroup.notify(queue: DispatchQueue.main) {
            completion?(storedError)
        }
    }
  
  fileprivate func postContentAddedNotification() {
    NotificationCenter.default.post(name: Notification.Name(rawValue: photoManagerContentAddedNotification), object: nil)
  }
}
