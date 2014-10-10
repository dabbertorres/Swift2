$(document).ready(function()
{
	$("#forkme_banner").mouseenter(function()
	{
		$(this).animate(
		{
			height: "+=50"
		}, 500);
	});
	
	$("#forkme_banner").mouseleave(function()
	{
		$(this).animate({
			height: "-=50"
		}, 500);
	});
});
