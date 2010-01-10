// $Id: jquery.drilldown.js,v 1.1.2.1 2010/01/10 16:24:40 yhahn Exp $

/**
 * Generic menu drilldown plugin for standard Drupal menu tree markup.
 * The plugin should be inited against a DOM element that *contains*
 * a Drupal ul.menu tree. Example:
 * 
 *   $('div.block-menu').drilldown('init', params);
 * 
 * You must provide the following parameters as settings:
 * 
 *   var params = {
 *     activePath : A drupal menu path that is currently active including the basePath e.g. "/mysite/node"
 *     trail : A jquery selector to the DOM element that should act as the trail container, e.g. "div.my-menu-breadcrumb-trail"
 *   }
 *
 */
(function($) {
  $.fn.drilldown = function(method, settings) {
    var menu = this;

    switch (method) {
      case 'setActive':
        var breadcrumb = [];
        var activeMenu;

        $(settings.activeLink).each(function() {
          // Traverse backwards through menu parents and build breadcrumb array.
          $(this).parents('ul.menu').each(function() {
            $(this).siblings('a').each(function() {
              breadcrumb.unshift($(this));
            });
          });

          // If we have a child menu (actually a sibling in the DOM), use it
          // as the active menu. Otherwise treat our direct parent as the
          // active menu.
          if ($(this).next().is('ul.menu')) {
            activeMenu = $(this).next();
            breadcrumb.push($(this));
          }
          else {
            activeMenu = $(this).parents('ul.menu');
          }
          if (activeMenu) {
            $('ul.menu', menu).removeClass('drilldown-active-menu').removeClass('clear-block');
            $(activeMenu[0]).addClass('drilldown-active-menu').addClass('clear-block').parents('li').show();
          }
        });

        // Render the breadcrumb to the target DOM object
        if (breadcrumb.length > 0) {
          var trail = $(settings.trail);
          trail.empty();
          for (var key in breadcrumb) {
            if (breadcrumb[key]) {
              $(breadcrumb[key]).clone().addClass('depth-'+key).appendTo(trail);
            }
          }
          $('a', trail).click(function() {
            var url = $(this).attr('href');
            settings.activeLink = $('ul.menu a[href='+url+']', menu);
            menu.drilldown('setActive', settings);
            return false;
          });
        }

        // Event in case others need to update themselves when a new active
        // link is s set.
        $(menu).trigger('refresh.drilldown');
        break;
      case 'init':
        $(menu).addClass('drilldown');
        $(settings.trail).addClass('drilldown-trail');

        // Set initial active menu state.
        var activeLink;
        if (settings.activePath && $('ul.menu a[href='+settings.activePath+']', menu).size() > 0) {
          activeLink = $('ul.menu a[href='+settings.activePath+']', menu).addClass('active');
        }
        if (!activeLink) {
          activeLink = $('ul.menu a.active', menu).size() ? $('ul.menu a.active', menu) : $('ul.menu > li > a', menu);
        }
        if (activeLink) {
          menu.drilldown('setActive', {'activeLink': $(activeLink[0]), 'trail': settings.trail});
        }

        // Attach click handlers to menu items
        $('ul.menu li:not(.leaf)', this).click(function() {
          if ($(this).parent().is('.drilldown-active-menu')) {
            if (menu.data('disableMenu')) {
              return true;
            }
            else {
              var url = $(this).children('a').attr('href');
              var activeLink = $('ul.menu a[href='+url+']', menu);
              menu.drilldown('setActive', {'activeLink': activeLink, 'trail': settings.trail});
              return false;
            }
          }
        });
        $('ul.menu li:not(.leaf) a', menu).click(function() {
          menu.data('disableMenu', true);
        });
        break;
    }
    return this;
  };
})(jQuery);
