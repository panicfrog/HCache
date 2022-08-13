Pod::Spec.new do |spec|

  spec.name         = "HCacheiOS"
  spec.version      = "0.0.1"
  spec.summary      = "A short description of HCache cpp."

  spec.description  = <<-DESC
  HCache cpp
                   DESC

  spec.homepage     = "http://github.com/panicfrog/HCache"

  spec.license      = "MIT"
  
#  spec.public_header_files = 'build/HCache.xcframework/ios-arm64_armv7_armv7s/Headers/**/*.{hpp,h}'
  
  spec.source_files = [
    'src/main/swift/*.swift',
    'src/main/swift/*.h',
    'src/main/swift/*.mm',
    'src/main/swift/*.m',
#    'build/HCache.xcframework/ios-arm64_armv7_armv7s/Headers/**/*.{hpp,h}'
  ]

  spec.author             = { "yeyongping" => "burnedfrog@gmail.com" }
  spec.platform     = :ios, "10.0"

  spec.source       = { :git => "http://github.com/panicfrog/HCach.git", :tag => "#{spec.version}" }
  
  spec.swift_version = '5.5'

  spec.ios.vendored_frameworks = 'build/HCache.xcframework'

end
