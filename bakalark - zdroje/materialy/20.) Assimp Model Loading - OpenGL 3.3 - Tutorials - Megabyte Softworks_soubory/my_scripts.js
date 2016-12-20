$(document).ready(function()
{
  // For showing reply forms

	$('a[id*=reply_]').each(function(){
    $(this).click(function(){
      $('#comm_'+this.id.substr(6)).toggle(500);
		  return false;
	  });
  });
  
  // For adding smileys
  
  $('a[name*=addSmiley_]').each(function(){
    $(this).click(function(){
      var iID = parseInt(this.name.substr(10));
      var sAppend = '*';
      if(iID < 10)sAppend += '0';
      sAppend += iID;
      sAppend += '*';
      $(this).parent().eq(0).parent().get(0).comment.value += sAppend;
      return false;
    });
  });

  // For displaying / hiding smileys

	$('a[name=toggleSmileys]').each(function(){
    $(this).click(function(){
      $(this).parent().eq(0).children('div[title=smileys]').eq(0).toggle(500);
		  return false;
	  });
  });
  
  // Validation of comment input
  
  $('form[name=addComment]').submit(function(){
    var theForm = $(this);
    if(theForm.attr('name') == 'addComment')
    {
      var sName = theForm.get(0).meno.value;
      var sEmail = theForm.get(0).email.value;
      var sComment = theForm.get(0).comment.value;
      var sCaptcha = theForm.get(0).captcha.value;
      
      var sMessages = [
      "Following errors occured:\n", 
      "-Name is missing",
      "-E-mail isn't valid",
      "-No comment entered",
      "-Text from image wasn't entered"
      ];
      var sFinalMessage = sMessages[0];
      var focusElement = null;
      if(sName == "")
      {
        sFinalMessage += "\n"+sMessages[1];
        focusElement = theForm.get(0).meno;
      }
      if(sEmail != "")
      {
        var iAtSign =  sEmail.indexOf('@');
        var iDotSign = sEmail.indexOf('.');
      	if(iAtSign == -1 || iDotSign == -1)
      	{
          sFinalMessage += "\n"+sMessages[2];
          if(focusElement == null)focusElement = theForm.get(0).email;
        }
      }
      if(sComment == "")
      {
        sFinalMessage += "\n"+sMessages[3];
        if(focusElement == null)focusElement = theForm.get(0).comment;
      }
      if(sCaptcha == "")
      {
        sFinalMessage += "\n"+sMessages[4];
        if(focusElement == null)focusElement = theForm.get(0).captcha;
      }
      if(sFinalMessage == sMessages[0])return true;
      else
      {
        alert(sFinalMessage);
        focusElement.focus();
      }
      return false;
    } 
  });
});
