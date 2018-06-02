$(function() {

    var newHash      = "",
        $mainContent = $("#centre-content"),
        $pageWrap    = $("#page-wrap"),
        baseHeight   = 0,
        $el;

    $pageWrap.height($pageWrap.height());
    baseHeight = $pageWrap.height() - $mainContent.height();

    $("nav").delegate("a", "click", function() {
        if ($(this).attr("href") != "javascript:void(0);") {
            window.location.hash = $(this).attr("href");
            return false;
        }
    });

    $(window).bind('hashchange', function(){

        newHash = window.location.hash.substring(1);

        if (newHash) {
            $mainContent
                .find("#guts")
                .fadeOut(200, function() {
                    $mainContent.hide().load(newHash + " #guts", function() {
                        $mainContent.fadeIn(200, function() {
                            // $pageWrap.animate({
                            //     height: baseHeight + $mainContent.height() + "px"
                            // });
                        });
                        $("nav a").removeClass("current");
                        $("nav a[href="+newHash+"]").addClass("current");
                    });
                });
        };

    });

    $(window).trigger('hashchange');

});