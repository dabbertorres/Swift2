$(document).ready(function()
{
	$("#forkme_banner").mouseenter(function()
	{
		$(this).animate(
		{
			height: "+=50"
		}, 500, function()
		{
			alert("Animation done");
		});
	});
});
