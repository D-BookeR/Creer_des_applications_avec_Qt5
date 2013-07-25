function keyColour(text, colour) {
    var iterate = function (container) {
        for(var i = 0; i < container.children.length; ++i) {
            if(container.children[i].evalText == text) {
                if(colour)
                    container.children[i].textColour = colour
                else
                    container.children[i].colourDefault()
                break;
            }
        }
    }
    iterate(keyboard)
    iterate(operations)
}

function handleKey(causeEvaluation, text, colour) {
    if(colour) {
        keyColour(text, colour)
    }

    if(! causeEvaluation) {
        main.computation += text
    } else {
        model.append({
                         computation: main.computation,
                         result: eval(main.computation)
                     })
        main.computation = ""
        resultview.currentIndex = model.count - 1
    }
}

function evalToUser(string) {
    return string.replace("-", "–")
                 .replace("*", "×")
                 .replace("/", "÷")
}
