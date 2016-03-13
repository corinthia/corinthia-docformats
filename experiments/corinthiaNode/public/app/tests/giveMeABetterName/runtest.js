function performTest(api) {
    api.cursor.insertCharacter("I");
    api.cursor.insertCharacter("T");
    api.cursor.insertCharacter("S");
    api.cursor.insertCharacter("M");
    api.cursor.insertCharacter("E");

    angular.element(document.getElementById('TestDiv')).scope().saveDoc();
}
