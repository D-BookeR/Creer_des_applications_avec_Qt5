import QtQuick 2.0
import QtTest 1.0

TestCase {
    name: "Declarative vs. imperative"
    when: windowShown

    width: 1
    height: 1

    function benchmark_declarative() {
        testClick(decl)
    }

    function benchmark_imperative() {
        testClick(imp)
    }

    function testClick(component) {
        mousePress(component, 0, 0)
    }

    Declarative {
        id: decl
    }

    Imperative {
        id: imp
    }
}

