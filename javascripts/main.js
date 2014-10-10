$(document).ready(function()
{
	$("#forkme_banner").hover(
	function()
	{
		$(this).animate(
		{
			paddingTop: "+=30",
			height: "+=40"
		}, 500);
	}, 
	function()
	{
		$(this).animate(
		{
			paddingTop: "-=30",
			height: "-=40"
		}, 500);
	});
});
