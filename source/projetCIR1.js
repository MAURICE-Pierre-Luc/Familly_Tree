function menu(){
    let hiverElem = document.getElementsByClassName("drop-contenu")[0].children[3];
    let étéElem = document.getElementsByClassName("drop-contenu")[0].children[1];
    let printempsElem = document.getElementsByClassName("drop-contenu")[0].children[0];
    let automneElem = document.getElementsByClassName("drop-contenu")[0].children[2];

    hiverElem.addEventListener("click", hiverClickHandler);
    printempsElem.addEventListener("click", printempsClickHandler);
    automneElem.addEventListener("click", automneClickHandler);
    étéElem.addEventListener("click", étéClickHandler);
}

function hiverClickHandler(){
    let colorFooter = document.querySelector("footer");
    colorFooter.style.backgroundColor = "#B0E0E6";
    let colorHeader = document.querySelector("nav");
    colorHeader.style.backgroundColor = "#F0F8FF";
    let bodyElem = document.querySelector("body");
    bodyElem.style.backgroundColor = "#FFFFFF";
    let textHeader = document.getElementById("Bienvenue");
    textHeader.style.color = "#B0E0E6";
    let buttonHeader = document.getElementById("randomRedirectButton");
    buttonHeader.style.color = "#B0E0E6";
    let accueil = document.getElementById("navbar-accueil");
    accueil.style.backgroundColor = "#F0F8FF";
    accueilText = document.getElementById("accueil");
    accueilText.style.color = "#B0E0E6";
    let déroulant = document.getElementsByClassName("drop-contenu")[0];
    déroulant.style.backgroundColor = "#F0F8FF";
    let submenuHeader = document.getElementById("submenu");
    submenuHeader.style.color = "#B0E0E6";
    let img = document.querySelectorAll("img")[0];
    img.src = "../source/image/depositphotos_49553431-stock-illustration-tree-without-leaves-isolated-on.jpg";
}
function automneClickHandler(){
    let colorFooter = document.querySelector("footer");
    colorFooter.style.backgroundColor = "#D0D5D9";
    let colorHeader = document.querySelector("nav");
    colorHeader.style.backgroundColor = "#FE6E00";
    let bodyElem = document.querySelector("body");
    bodyElem.style.backgroundColor = "#FFFFFF";
    let textHeader = document.getElementById("Bienvenue");
    textHeader.style.color = "#D0D5D9";
    let buttonHeader = document.getElementById("randomRedirectButton");
    buttonHeader.style.color = "#D0D5D9";
    let accueil = document.getElementById("navbar-accueil");
    accueil.style.backgroundColor = "#FE6E00";
    accueilText = document.getElementById("accueil");
    accueilText.style.color = "#D0D5D9";
    let déroulant = document.getElementsByClassName("drop-contenu")[0];
    déroulant.style.backgroundColor = "#FE6E00";
    let submenuHeader = document.getElementById("submenu");
    submenuHeader.style.color = "#D0D5D9";
    let img = document.querySelectorAll("img")[0];
    img.src = "../source/image/arbre-automne-feuilles-qui-tombent-illustration-style-dessin-anime_976369-882.avif";
}
function étéClickHandler(){
    let colorFooter = document.querySelector("footer");
    colorFooter.style.backgroundColor = "#FAB300";
    let colorHeader = document.querySelector("nav");
    colorHeader.style.backgroundColor = "#FEFEE2";
    let bodyElem = document.querySelector("body");
    bodyElem.style.backgroundColor = "#FFFFFF";
    let textHeader = document.getElementById("Bienvenue");
    textHeader.style.color = "#56E100";
    let buttonHeader = document.getElementById("randomRedirectButton");
    buttonHeader.style.color = "#56E100";
    let accueil = document.getElementById("navbar-accueil");
    accueil.style.backgroundColor = "#FEFEE2";
    accueilText = document.getElementById("accueil");
    accueilText.style.color = "#56E100";
    let déroulant = document.getElementsByClassName("drop-contenu")[0];
    déroulant.style.backgroundColor = "#FEFEE2";
    let submenuHeader = document.getElementById("submenu");
    submenuHeader.style.color = "#56E100";
    let img = document.querySelectorAll("img")[0];
    img.src = "../source/image/depositphotos_5148911-stock-illustration-big-tree.jpg";
}
function printempsClickHandler(){
    let colorFooter = document.querySelector("footer");
    colorFooter.style.backgroundColor = "#6FEB66";
    let colorHeader = document.querySelector("nav");
    colorHeader.style.backgroundColor = "#DE3163";
    let bodyElem = document.querySelector("body");
    bodyElem.style.backgroundColor = "#FFFFFF";
    let textHeader = document.getElementById("Bienvenue");
    textHeader.style.color = "#6FEB66";
    let buttonHeader = document.getElementById("randomRedirectButton");
    buttonHeader.style.color = "#6FEB66";
    let accueil = document.getElementById("navbar-accueil");
    accueil.style.backgroundColor = "#DE3163";
    accueilText = document.getElementById("accueil");
    accueilText.style.color = "#6FEB66";
    let déroulant = document.getElementsByClassName("drop-contenu")[0];
    déroulant.style.backgroundColor = "#DE3163";
    let submenuHeader = document.getElementById("submenu");
    submenuHeader.style.color = "#6FEB66";
    let img = document.querySelectorAll("img")[0];
    img.src = "../source/image/depositphotos_187733090-stock-illustration-spring-tree-with-flowers-isolated.jpg";
}

const sizeElement = document.getElementById('size');
const sizeContent = sizeElement.textContent || sizeElement.innerText;
document.getElementById('randomRedirectButton').addEventListener('click', function() {
    redirectToRandomPage(sizeContent);
});
function redirectToRandomPage(max) { 
    const randomLink = `../export/${Math.floor(Math.random() * max) + 1}.html`;
    window.location.href = randomLink;
}




function main(){
    menu();
}
main();