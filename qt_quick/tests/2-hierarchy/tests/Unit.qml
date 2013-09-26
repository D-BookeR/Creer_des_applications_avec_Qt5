import QtQuick 2.0
import QtTest 1.0

TestCase {
    name: "SimpleTests"

    function test_math() {
        compare(1 + 1, 2, "1 + 1 = 2")
    }

    function test_fail() {
        compare(4 - 2, 3, "Failed math test")
    }
}
