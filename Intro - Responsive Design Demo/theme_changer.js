function goRed() {
	document.getElementById("header").style.backgroundImage = "linear-gradient(to right, #993300, #990000)";
	document.getElementById("footer").style.backgroundImage = "linear-gradient(to right, #993300, #990000)";
	document.getElementById("main").style.backgroundColor = "#660000";
	var navButtons = document.getElementsByClassName("nav-button");
	var styleButtons = document.getElementsByClassName("style-button");
	
	for (i = 0; i < navButtons.length; i++) {
		navButtons[i].style.backgroundColor = "#993300";
	}
	
	for (i = 0; i < styleButtons.length; i++) {
		styleButtons[i].style.backgroundColor = "#993300";
	}
}

function goGreen() {
	document.getElementById("header").style.backgroundImage = "linear-gradient(to right, #006600, #009900)";
	document.getElementById("footer").style.backgroundImage = "linear-gradient(to right, #006600, #009900)";
	document.getElementById("main").style.backgroundColor = "#003300";
	var navButtons = document.getElementsByClassName("nav-button");
	var styleButtons = document.getElementsByClassName("style-button");
	
	for (i = 0; i < navButtons.length; i++) {
		navButtons[i].style.backgroundColor = "#006600";
	}
	
	for (i = 0; i < styleButtons.length; i++) {
		styleButtons[i].style.backgroundColor = "#006600";
	}
}

function goYellow() {
	document.getElementById("header").style.backgroundImage = "linear-gradient(to right, #99CC00, #99FF00)";
	document.getElementById("footer").style.backgroundImage = "linear-gradient(to right, #99CC00, #99FF00)";
	document.getElementById("main").style.backgroundColor = "#999900";
	var navButtons = document.getElementsByClassName("nav-button");
	var styleButtons = document.getElementsByClassName("style-button");
	
	for (i = 0; i < navButtons.length; i++) {
		navButtons[i].style.backgroundColor = "#99CC00";
	}
	
	for (i = 0; i < styleButtons.length; i++) {
		styleButtons[i].style.backgroundColor = "#99CC00";
	}
}

function goPurple() {
	document.getElementById("header").style.backgroundImage = "linear-gradient(to right, #CC0099, #CC00FF)";
	document.getElementById("footer").style.backgroundImage = "linear-gradient(to right, #CC0099, #CC00FF)";
	document.getElementById("main").style.backgroundColor = "#CC0033";
	var navButtons = document.getElementsByClassName("nav-button");
	var styleButtons = document.getElementsByClassName("style-button");
	
	for (i = 0; i < navButtons.length; i++) {
		navButtons[i].style.backgroundColor = "#CC0099";
	}
	
	for (i = 0; i < styleButtons.length; i++) {
		styleButtons[i].style.backgroundColor = "#CC0099";
	}
}

function goDefault() {
	document.getElementById("header").style.backgroundImage = "linear-gradient(to right, #336666, #333366)";
	document.getElementById("footer").style.backgroundImage = "linear-gradient(to right, #336666, #333366)";
	document.getElementById("main").style.backgroundColor = "#003333";
	var navButtons = document.getElementsByClassName("nav-button");
	var styleButtons = document.getElementsByClassName("style-button");
	
	for (i = 0; i < navButtons.length; i++) {
		navButtons[i].style.backgroundColor = "#336666";
	}
	
	for (i = 0; i < styleButtons.length; i++) {
		styleButtons[i].style.backgroundColor = "#336666";
	}
}