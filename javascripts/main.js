$(document).ready(function()
{
	$("#forkme_banner").hover(
	function()
	{
		$(this).animate(
		{
			top: "+=25",
			height: "+=50"
		}, 500);
	}, 
	function()
	{
		$(this).animate(
		{
			top: "-=25",
			height: "-=50"
		}, 500);
	});
});
