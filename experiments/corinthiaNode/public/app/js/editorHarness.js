var allCode = null;
function readFile(filename) {
    var req = new XMLHttpRequest();
    req.open("GET", filename, false);
    req.send();
    return req.responseText;
}
function loadCode() {
    var modules = [
        "autoCorrect",
        "changeTracking",
        "clipboard",
        "collections",
        "cursor",
        "definitions",
        "dom",
        "editor",
        "elementTypes",
        "equations",
        "figures",
        "formatting",
        "hierarchy",
        "input",
        "lists",
        "main",
        "markdown",
        "metadata",
        "outline",
        "paragraph",
        "position",
        "postponedActions",
        "preview",
        "range",
        "scan",
        "selection",
        "styles",
        "tables",
        "text",
        "traversal",
        "types",
        "undo",
        "util",
        "viewport",
    ];
    var allCodeArray = new Array();
    allCodeArray.push(readJSCode("js/editor/first.js"));
    for (var i = 0; i < modules.length; i++)
        allCodeArray.push(readModule("js/editor", modules[i] + ".js"));
    allCode = allCodeArray.join("\n");
}
function readJSCode(filename) {
    var req = new XMLHttpRequest();
    req.open("GET", filename, false);
    req.send();
    return req.responseText;
}
function readModule(baseDir, filename) {
    var code = readJSCode(baseDir + "/" + filename);
    code = "window._nextDefineFilename = " + JSON.stringify(filename) + ";\n" + code;
    return code;
}
function loadEditorApi() {
    loadCode();
}
//# sourceMappingURL=testharness.js.map
 
