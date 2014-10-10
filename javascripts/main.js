$(document).ready(function()
{
	$("#forkme_banner").hover(
	function()
	{
		$(this).animate(
		{
			paddingTop: "+=" + $(this).height().toString(),
			height: ($(this).height() * 2)
		}, 500);
	}, 
	function()
	{
		$(this).animate(
		{
			paddingTop: "-=" + $(this).height().toString(),
			height: ($(this).height() / 2)
		}, 500);
	});
});
