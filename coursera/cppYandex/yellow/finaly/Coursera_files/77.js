(window.webpackJsonp=window.webpackJsonp||[]).push([[77],{"+38Z":function(module,exports,e){},JiLy:function(module,exports,e){var t=e("+38Z"),n;"string"==typeof t&&(t=[[module.i,t,""]]);var a={transform:void 0},s=e("aET+")(t,a);t.locals&&(module.exports=t.locals)},ZjXQ:function(module,e,t){"use strict";var n=t("VbXa"),a=t.n(n),s=t("pVnL"),r=t.n(s),o=t("sbe7"),i=t.n(o),c=t("y1LI"),u=t("17x9"),l=t.n(u),d=t("JiLy"),m=t.n(d),p=t("yhVA"),g=t.n(p);function MoreOrLess(e,t){var n=e.ariaProps,a=e.buttonContext,s=e.onClick,o=e.more,u=g()("Read more about #{buttonContext}",{buttonContext:a}),l=g()("Read less about #{buttonContext}",{buttonContext:a});return i.a.createElement("span",{className:"rc-MoreOrLess body-2-text color-hint-text"},o?i.a.createElement("button",r()({type:"button",onClick:s,"aria-label":u,className:"nostyle button-link"},n),g()("more")," ",i.a.createElement(c.a,{name:"chevron-down",className:"toggle-arrow"})):i.a.createElement("button",r()({type:"button",onClick:s,"aria-label":l,className:"nostyle button-link"},n),g()("less")," ",i.a.createElement(c.a,{name:"chevron-up",className:"toggle-arrow"})))}MoreOrLess.propTypes={more:l.a.bool,onClick:l.a.func,ariaProps:l.a.shape({"aria-controls":l.a.string,"aria-expanded":l.a.bool}),buttonContext:l.a.string};var b=function(e){function AssignmentInstructionSection(){for(var t,n=arguments.length,a=new Array(n),s=0;s<n;s++)a[s]=arguments[s];return(t=e.call.apply(e,[this].concat(a))||this).state={expanded:!0},t.toggleExpand=function(){t.setState(function(e){var t;return{expanded:!e.expanded}})},t}var t;return a()(AssignmentInstructionSection,e),AssignmentInstructionSection.prototype.render=function render(){var e=this.state.expanded,t="instructions-container-".concat((new Date).getTime()),n={"aria-controls":t,"aria-expanded":e},a=this.props,s=a.title,r=a.children;return i.a.createElement("div",{className:"rc-AssignmentInstructionSection"},i.a.createElement("div",{className:"title-container bgcolor-primary-light"},i.a.createElement("span",{className:"body-2-text"},s),i.a.createElement(MoreOrLess,{more:!e,onClick:this.toggleExpand,ariaProps:n,buttonContext:s})),e&&i.a.createElement("div",{className:"instructions-content-container",id:t,key:e},r))},AssignmentInstructionSection}(i.a.Component);b.propTypes={title:l.a.string,children:l.a.node},e.a=b},beVP:function(module,exports,e){var t=e("oZPO"),n;"string"==typeof t&&(t=[[module.i,t,""]]);var a={transform:void 0},s=e("aET+")(t,a);t.locals&&(module.exports=t.locals)},fxeD:function(module,e,t){"use strict";var n=t("VbXa"),a=t.n(n),s=t("17x9"),r=t.n(s),o=t("sbe7"),i=t.n(o),c=t("9can"),u=t("ZjXQ"),l=t("beVP"),d=t.n(l),m=function(e){function AssignmentInstructions(){return e.apply(this,arguments)||this}var t;return a()(AssignmentInstructions,e),AssignmentInstructions.prototype.render=function render(){var e=this.props.instructions;if(null==e)return null;return i.a.createElement("div",{className:"rc-AssignmentInstructions"},i.a.createElement("div",{className:"introduction"},i.a.createElement(c.a,{content:e.introduction,assumeStringIsHtml:!0})),e.sections&&e.sections.map(function(e){return i.a.createElement(u.a,{title:e.title,key:e.title},i.a.createElement(c.a,{content:e.content,assumeStringIsHtml:!0}))}))},AssignmentInstructions}(i.a.Component);m.propTypes={instructions:r.a.shape({introduction:r.a.any.isRequired,sections:r.a.arrayOf(r.a.shape({content:r.a.object.isRequired,title:r.a.string.isRequired}))})},e.a=m},oZPO:function(module,exports,e){},pr3t:function(module,e,t){"use strict";t.r(e);var n=t("sbe7"),a=t.n(n),s=t("8cuT"),r=t.n(s),o=t("VYij"),i=t.n(o),c=t("fxeD"),u=t("jsrg"),l=t("L1vm"),d=t("dAof"),m=t("sQ/U"),p=t("nLAy"),g=t("VMeS"),b=i.a.compose(l.a.createTrackedContainer(function(){return{namespace:{page:"peer_review_instructions"}}}),r()(["PeerAssignmentStore","PeerPermissionsAndProgressesStore","PeerViewSubmissionStore"],function(e,t){var n=e.PeerAssignmentStore,a=e.PeerPermissionsAndProgressesStore,s=e.PeerViewSubmissionStore,r,o=n.getState().assignment;return{hasLoaded:"loaded"===n.getState().loadState&&"loaded"===a.getState().loadState,instructions:o&&o.instructions,loadedPeerViewSubmissionId:s.getState().submissionId,isSubmitted:a.getState().isSubmitted,latestSubmissionId:a.getState().latestSubmissionId}}),Object(u.a)(function(e){var t;return e.hasLoaded},a.a.createElement(g.a,{className:"rc-PeerItemInstructions"})),Object(d.a)(function(e,t){var n=t.itemMetadata,a=t.isSubmitted,s=t.latestSubmissionId,r=t.loadedPeerViewSubmissionId,o;a&&s&&(r!==s&&e.executeAction(p.d,{userId:m.a.get().id,courseId:n.get("course").get("id"),itemId:n.get("id"),submissionId:s}))}))(c.a);e.default=b}}]);
//# sourceMappingURL=77.de84d3fd8a2336f917d7.js.map