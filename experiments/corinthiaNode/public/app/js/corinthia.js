function onload() {
    //alert("Top of the world, ma");
    var heads = document.getElementsByTagName("head");
    heads[0].innerHTML += '<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/3.1.1/css/bootstrap.min.css">';

    var bods = document.getElementsByTagName("body");

    var hdr = document.createElement("div");
    var att = document.createAttribute("class");
    att.value = "jumbotron";
    hdr.setAttributeNode(att);

    var h1 = document.createElement("h1");
    var t = document.createTextNode("Corinthia Node");
        h1.appendChild(t);
    hdr.appendChild(h1);
    addEditButton(hdr);
    addForm(hdr);
    var beforeThis = bods[0].childNodes[0];
    bods[0].insertBefore(hdr, beforeThis);
    var saveDataBttn = document.getElementById("SaveMe");
    saveDataBttn.disabled = true;
}

function addEditButton(hdr) {
    var btn = document.createElement("a");
    var t = document.createTextNode("Edit");

    var idatt = document.createAttribute("id");
    idatt.value = "editBtn";
    btn.setAttributeNode(idatt);

    var att = document.createAttribute("onclick");
    att.value = "editToggle()";
    btn.setAttributeNode(att);

    var cls = document.createAttribute("class");
    cls.value = "btn btn-success";
    btn.setAttributeNode(cls);

    btn.appendChild(t);
    hdr.appendChild(btn);
    }

function addForm(hdr) {
    var frm = document.createElement("form");

    var actatt = document.createAttribute("action");
    actatt.value = "/corput";
    frm.setAttributeNode(actatt);

    var enchatt = document.createAttribute("enctype");
    enchatt.value = "multipart/form-data";
    frm.setAttributeNode(enchatt);

    var methatt = document.createAttribute("method");
    methatt.value = "post";
    frm.setAttributeNode(methatt);

    var ip1 = document.createElement("input");
    var type1 = document.createAttribute("type");
    type1.value = "post";
    ip1.setAttributeNode(type1);
    var class1 = document.createAttribute("class");
    class1.value = "form-control";
    ip1.setAttributeNode(class1);
    var name1 = document.createAttribute("name");
    name1.value = "htmldata";
    ip1.setAttributeNode(name1);
    var id1 = document.createAttribute("id");
    id1.value = "saveData";
    ip1.setAttributeNode(id1);
    frm.appendChild(ip1);

    //we could try an XMLHttpRequest instead of form stuff?
    //need to get a handle on the document name too
    //have the get process write it into the meta data
    var ip2 = document.createElement("input");
    var id2 = document.createAttribute("id");
    id2.value = "SaveMe";
    ip2.setAttributeNode(id2);
    var type2 = document.createAttribute("type");
    type2.value = "submit";
    ip2.setAttributeNode(type2);
    var class2 = document.createAttribute("class");
    class2.value = "btn btn-danger";
    ip2.setAttributeNode(class2);
    var name2 = document.createAttribute("name");
    name2.value = "SaveMe";
    ip2.setAttributeNode(name2);
    var val2 = document.createAttribute("value");
    val2.value = "Save";
    ip2.setAttributeNode(val2);
    frm.appendChild(ip2);

    //Need to strip off the header and the js?

    hdr.appendChild(frm);
}

function editToggle() {
        var bod = document.getElementsByTagName("body");
        var bttn = document.getElementById("editBtn");
        var saveBttn = document.getElementById("SaveMe");
        if(bod[0].contentEditable == "true") {
            bod[0].contentEditable = "false";
            bttn.text = "Edit";
            var saveDataBttn = document.getElementById("saveData");
            saveDataBttn.value = "<html>" + document.documentElement.innerHTML + "</html>";
            saveBttn.disabled = false;
        } else {
            bod[0].contentEditable = "true";
            bttn.text = "View Only";
            saveBttn.disabled = true;
        }
}
