$(document).ready(function () {
	$("#edu-but").click(function () {
		$("#about-me").hide();
		$("#skills").hide();
		$("#experience").hide();
		$("#extracurriculars").hide();
		$("#education").slideDown();
	});
	$("#about-but").click(function () {
		$("#education").hide();
		$("#skills").hide();
		$("#experience").hide();
		$("#extracurriculars").hide();
		$("#about-me").slideDown();
	});
	$("#skills-but").click(function () {
		$("#education").hide();
		$("#about-me").hide();
		$("#experience").hide();
		$("#extracurriculars").hide();
		$("#skills").slideDown();
	});
	$("#exp-but").click(function () {
		$("#education").hide();
		$("#about-me").hide();
		$("#skills").hide();
		$("#extracurriculars").hide();
		$("#experience").slideDown();
	});
	$("#extra-but").click(function () {
		$("#education").hide();
		$("#about-me").hide();
		$("#skills").hide();
		$("#experience").hide();
		$("#extracurriculars").slideDown();
	});
});