//
//  HCache.swift
//  HCacheExample
//
//  Created by 叶永平 on 2022/8/12.
//

import Foundation

public struct ObjectString {
  public var content: String
}

public protocol HCacheValue {
  func `set`(key: String, delegate: HCacheWrapper)
}

extension Int32: HCacheValue {
  public func set(key: String, delegate: HCacheWrapper) {
    delegate.setIntValue(self, forKey: key)
  }
}
extension Double: HCacheValue {
  public func set(key: String, delegate: HCacheWrapper) {
    delegate.setDoubleValue(self, forKey: key)
  }

}
extension Float: HCacheValue {
  public func set(key: String, delegate: HCacheWrapper) {
    delegate.setFloatValue(self, forKey: key)
  }
}
extension Int: HCacheValue {
  public func set(key: String, delegate: HCacheWrapper) {
    delegate.setLongValue(self, forKey: key)
  }
}
extension Bool: HCacheValue {
  public func set(key: String, delegate: HCacheWrapper) {
    delegate.setBoolValue(self, forKey: key)
  }
}
extension String: HCacheValue {
  public func set(key: String, delegate: HCacheWrapper) {
    delegate.setStringValue(self, forKey: key, isObject: false)
  }

}
extension ObjectString: HCacheValue {
  public func set(key: String, delegate: HCacheWrapper) {
    delegate.setStringValue(self.content, forKey: key, isObject: true)
  }
}

public class HCacheSwift {
  
  public static let shared = HCacheSwift()
  
  static var isSetup: Bool {
    return path != nil
  }
  
  private let wrapper = HCacheWrapper()
  
  private static var path: String?
  
  public class func setup(_ path: String){
    HCacheSwift.path = path
  }
  
  private init() {
    guard let path = HCacheSwift.path else {
      fatalError("Error - you must call setup before accessing HCache.shared")
    }
    wrapper.setup(withPath: path)
  }
  
  public func set<T: HCacheValue>(value: T, for key: String) {
    value.set(key: key, delegate: wrapper)
  }
    
  public func setObject(value: String, key: String) {
      ObjectString(content: value).set(key: key, delegate: wrapper)
  }
  
    public func getBool(for key: String) -> Bool? {
        let value = wrapper.getCacheValue(forKey: key)
        guard value.isBOOL() else { return nil }
        return value.boolVlaue()
    }
    
    public func getInt32(for key: String) -> Int32? {
        let value = wrapper.getCacheValue(forKey: key)
        guard value.isInt() else { return nil }
        return value.intValue()
    }
    
    public func getInt(for key: String) -> Int? {
        let value = wrapper.getCacheValue(forKey: key)
        guard value.isLong() else { return nil }
        return value.longVlaue()
    }
    
    public func getFloat(for key: String) -> Float? {
        let value = wrapper.getCacheValue(forKey: key)
        guard value.isFloat() else { return nil }
        return value.floatValue()
    }
    
    public func getDouble(for key: String) -> Double? {
        let value = wrapper.getCacheValue(forKey: key)
        guard value.isDouble() else { return nil }
        return value.doubleValue()
    }
    
    public func getString(for key: String) -> String? {
        let value = wrapper.getCacheValue(forKey: key)
        guard value.isString() else { return nil }
        return value.stringValue()
    }
    
    public func getJsonString(for key: String) -> String? {
        let value = wrapper.getCacheValue(forKey: key)
        guard value.isJsonString() else { return nil }
        return value.jsonValue()
    }
  
}
