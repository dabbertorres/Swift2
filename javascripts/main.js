$(document).ready(function()
{
	$("#forkme_banner").hover(
	function()
	{
		$(this).animate(
		{
			height: "+=50"
		}, 500);
	}, 
	function()
	{
		$(this).animate(
		{
			height: "-=50"
		}, 500);
	});
});
