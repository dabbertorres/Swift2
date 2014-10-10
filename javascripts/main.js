$(document).ready(function()
{
	$("#forkme_banner").hover(
	function()
	{
		$(this).animate(
		{
			paddingTop: "+=30",
			height: ($(this).height() * 2)
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
