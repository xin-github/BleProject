package com.pupupula.blelib.util

/**
 * @author TuXin
 * @date 2019-10-28 11:05.
 *
 * Email : tuxin@pupupula.com
 */
const val LIGHT_SEARCH_NAME_LENGTH = 9
const val LIGHT_SEARCH_START_WITH = "LB"
val LIGHT_SEARCH_NAME_BATCH_INDEX = intArrayOf(2, 3)
const val LIGHT_SEARCH_NAME_COLOR_INDEX = 4
val LIGHT_SEARCH_NAME_LIGHT_NUM = intArrayOf(5, 6, 7, 8)

fun isSearchLightNameValidate(name: String?): Boolean {
    if (name.isNullOrEmpty()) return false
    if (name.length != LIGHT_SEARCH_NAME_LENGTH || !name.startsWith(LIGHT_SEARCH_START_WITH)) {
        return false
    }

    val batchNum = try {
        val batchNumStr = name.substring(LIGHT_SEARCH_NAME_BATCH_INDEX[0], LIGHT_SEARCH_NAME_BATCH_INDEX[1] + 1)
        Integer.parseInt(batchNumStr, 16)
    } catch (e: Exception) {
        -1
    }
    if (batchNum == -1) {
        return false
    }

    val isColorBitValidate = name[LIGHT_SEARCH_NAME_COLOR_INDEX].isLetter()
    if (!isColorBitValidate) {
        return false
    }

    val lightNum = try {
        val batchNumStr = name.substring(LIGHT_SEARCH_NAME_LIGHT_NUM[0], name.length)
        Integer.parseInt(batchNumStr, 16)
    } catch (e: Exception) {
        -1
    }
    return lightNum != -1
}

/**
 * This function will not check is name validate, before call this method, please make sure
 * the name is validate by {isSearchLightNameValidate(name)}
 * */
fun convertLightSearchNameToSN(name: String): String {
    val sb = StringBuilder(name)
    sb.insert(2, "CB")
    sb.insert(LIGHT_SEARCH_NAME_BATCH_INDEX[1] + 3, "00")

    // already inset two bytes, so color index will will offset 2
    when (sb[LIGHT_SEARCH_NAME_COLOR_INDEX + 4]) {
        'G' -> sb.insert(LIGHT_SEARCH_NAME_COLOR_INDEX + 5, "Y")
        'Y' -> sb.insert(LIGHT_SEARCH_NAME_COLOR_INDEX + 5, "L")
        'E' -> sb.insert(LIGHT_SEARCH_NAME_COLOR_INDEX + 5, "N")
        'R' -> sb.insert(LIGHT_SEARCH_NAME_COLOR_INDEX + 5, "D")
    }

    return sb.toString()
}