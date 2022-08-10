//
// Created by 叶永平 on 2022/8/9.
//

#ifndef HCACHE_CACHEJNI_H
#define HCACHE_CACHEJNI_H

#include <jni.h>
#include "KVSingleton.hpp"

#ifdef __cplusplus
extern "C" {
#endif
std::string jstring2string(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

const char * getPathField(JNIEnv *env, jobject thiz) {
    const jclass obj = env->GetObjectClass(thiz);
    const jfieldID pathID = env->GetFieldID(obj, "path", "Ljava/lang/String;");
    const jstring path = (jstring)env->GetObjectField(thiz, pathID);
    jboolean isCopy;
    const char *_path = env->GetStringUTFChars(path, &isCopy);
    env->DeleteLocalRef(obj);
    env->DeleteLocalRef(path);
    return _path;
}

JNIEXPORT jboolean JNICALL
Java_HCache_HCacheLibrary_initKv(JNIEnv *env, jobject thiz) {
    const char *_path = getPathField(env, thiz);
    if (_path == NULL) {
        return JNI_FALSE;
    }
    cache::KVSingleton::getInstance().getKV(_path);
    return JNI_TRUE;
}

//JNIEXPORT jboolean JNICALL
//Java_HCache_HCacheLibrary_get(JNIEnv *env, jobject thiz, jstring key) {
//    const char *_path = getPathField(env, thiz);
//    if (_path == NULL) {
//        return JNI_FALSE;
//    }
//    auto kv = cache::KVSingleton::getInstance().getKV(_path);
//    auto _key = jstring2string(env, key);
//    auto value = kv->getValue(_key);
//    /// TODO 转成kotlin原生类型
//    return JNI_TRUE;
//}

JNIEXPORT jboolean JNICALL
Java_HCache_HCacheLibrary_get(JNIEnv *env, jobject thiz, jstring key, jobject value) {
    const char *_path = getPathField(env, thiz);
    if (_path == NULL) {
        return JNI_FALSE;
    }
    auto kv = cache::KVSingleton::getInstance().getKV(_path);
    auto _key = jstring2string(env, key);
    auto cValue = kv->getValue(_key);
    const jclass valueObj = env->GetObjectClass(thiz);
    const jfieldID typeID = env->GetFieldID(valueObj, "type", "Ljava/lang/String;");
    const jfieldID valueID = env->GetFieldID(valueObj, "value", "Ljava/lang/Object;");
    /// type int-> 'I', long-> 'L', float-> 'F', double-> 'D', boolean-> 'B', string-> 'S', objectString-> 'OS', None-> 'N'

//    typedef uint8_t  jboolean; /* unsigned 8 bits */
//    typedef int8_t   jbyte;    /* signed 8 bits */
//    typedef uint16_t jchar;    /* unsigned 16 bits */
//    typedef int16_t  jshort;   /* signed 16 bits */
//    typedef int32_t  jint;     /* signed 32 bits */
//    typedef int64_t  jlong;    /* signed 64 bits */
//    typedef float    jfloat;   /* 32-bit IEEE 754 */
//    typedef double   jdouble;  /* 64-bit IEEE 754 */
    if (cValue.isBool()) {
        auto v =  cValue.getBool();
        env->SetBooleanField(value, valueID, v ? JNI_TRUE : JNI_FALSE);
        env -> SetObjectField(value,typeID,env->NewStringUTF("B"));
    } else if (cValue.isInt()) {
        /// TODO 需要考虑int是否是int32_t
        auto v =  cValue.getInt();
        env->SetIntField(value, valueID, v);
        env -> SetObjectField(value,typeID,env->NewStringUTF("I"));
    } else if (cValue.isLong()) {
        auto v =  cValue.getLong();
        env -> SetObjectField(value,typeID,env->NewStringUTF("L"));
    } else if (cValue.isFloat()) {
        auto v =  cValue.getFloat();
        env -> SetObjectField(value,typeID,env->NewStringUTF("F"));
    } else if (cValue.isDouble()) {
        auto v =  cValue.getDouble();
        env -> SetObjectField(value,typeID,env->NewStringUTF("D"));
    } else if (cValue.isString()) {
        auto v =  cValue.getString();
        env -> SetObjectField(value,typeID,env->NewStringUTF("S"));
    } else if (cValue.isJsonString()) {
        auto v =  cValue.getJsonString();
        env -> SetObjectField(value,typeID,env->NewStringUTF("OS"));
    } else if (cValue.isNull()) {
        env -> SetObjectField(value,typeID,env->NewStringUTF("N"));
    }
    env->DeleteLocalRef(valueObj);
    /// TODO 转成kotlin原生类型
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL
Java_HCache_HCacheLibrary_setBoolean(JNIEnv *env, jobject thiz, jstring key, jboolean value) {
    const char *_path = getPathField(env, thiz);
    if (_path == NULL) {
        return JNI_FALSE;
    }
    auto kv = cache::KVSingleton::getInstance().getKV(_path);
    // TODO: implement setBoolean()
}

JNIEXPORT jboolean JNICALL
Java_HCache_HCacheLibrary_setInt(JNIEnv *env, jobject thiz, jstring key, jint value) {
    const char *_path = getPathField(env, thiz);
    if (_path == NULL) {
        return JNI_FALSE;
    }
    auto kv = cache::KVSingleton::getInstance().getKV(_path);
    // TODO: implement setInt()
}

JNIEXPORT jboolean JNICALL
Java_HCache_HCacheLibrary_setDouble(JNIEnv *env, jobject thiz, jstring key, jdouble value) {
    const char *_path = getPathField(env, thiz);
    if (_path == NULL) {
        return JNI_FALSE;
    }
    auto kv = cache::KVSingleton::getInstance().getKV(_path);
    // TODO: implement setDouble()
}

JNIEXPORT jboolean JNICALL
Java_HCache_HCacheLibrary_setString(JNIEnv *env, jobject thiz, jstring key, jstring value) {
    const char *_path = getPathField(env, thiz);
    if (_path == NULL) {
        return JNI_FALSE;
    }
    auto kv = cache::KVSingleton::getInstance().getKV(_path);
    // TODO: implement setString()
}

JNIEXPORT jboolean JNICALL
Java_HCache_HCacheLibrary_setObjectString(JNIEnv *env, jobject thiz, jstring key, jstring value) {
    const char *_path = getPathField(env, thiz);
    if (_path == NULL) {
        return JNI_FALSE;
    }
    auto kv = cache::KVSingleton::getInstance().getKV(_path);
    // TODO: implement setObjectString()
}

#ifdef __cplusplus
};
#endif


#endif //HCACHE_CACHEJNI_H

