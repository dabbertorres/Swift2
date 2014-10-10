$(document).ready(function()
{
	$("#forkme_banner").hover(
	function()
	{
		$(this).animate(
		{
			paddingTop: "+=25",
			height: "+=50"
		}, 500);
	}, 
	function()
	{
		$(this).animate(
		{
			paddingTop: "-=25",
			height: "-=50"
		}, 500);
	});
});
