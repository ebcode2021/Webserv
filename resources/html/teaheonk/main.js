'use strict';

// 이벤트에 등록하는 콜백함수는 최대한 간단하고 무겁지 않게 
// => 이벤트는 중복 실행이 안되기 때문

// Make Navbar transparent when it is on top
const navbar = document.querySelector('#navbar');
let navbar_height = navbar.getBoundingClientRect().height;
// offsetHeight = 원래 지정된 사이즈 (height), transform 무시
// getBoundingClientRect() = 사용자가 보는 사이즈, transform 적용
// clientHeight = css상 높이 + css상 내부 여백 - 수평 스크롤바의 높이(존재하는 경우에만)
// scrollHeight = scroll 없이 요소의 콘텐츠를 모두 나타낼 때 필요한 최소 높이 값. 반올림

document.addEventListener('scroll',() => {
    if(window.scrollY > navbar_height) {
        navbar_toggle_btn.classList.add('navbar--dark');
        navbar.classList.add('navbar--dark');
    } else {
        navbar_toggle_btn.classList.remove('navbar--dark');
        navbar.classList.remove('navbar--dark');
    } 
    // navar--dark는 BEM의 Modifier 사용
})

// Handle toggle button for small screen
const navbar_toggle_btn = document.querySelector('.navbar__toggle-btn');

navbar_toggle_btn.addEventListener('click', () => {
    navbar_menu.classList.toggle('open');
})

// Handle scroll when tapping on navbar menu
const navbar_menu = document.querySelector('.navbar__menu');
const navbar_menu_btn = document.querySelectorAll('.navbar__menu__item');

navbar_menu.addEventListener('click',(e) => {
    const target = e.target;
    const link = target.dataset.link;


    if(link === null) {
        return;
    }

    navbar_menu.classList.remove('open');

    // Method 1
    // const scroll_to = document.querySelector(link);
    // scroll_to.scrollIntoView({behavior : 'smooth'});

    // Mehtod 2
    const scroll_to = document.querySelector(link).offsetTop;
    navbar_height = navbar.getBoundingClientRect().height;
    window.scrollTo({top : scroll_to - navbar_height, behavior : 'smooth'});
    select_nav_item(target);
})

// Handle click on 'Contact Me' button on home
const home_contact_btn = document.querySelector('.home__contact');

home_contact_btn.addEventListener('click', () => {
    scroll_into_view("#contact");
})

// Make home slowly fade to transparent as the window scroll down


const home_container = document.querySelector('.home__container');
const home_container_height = home_container.getBoundingClientRect().height;

document.addEventListener('scroll', () => {
    // console.log(1 - window.scrollY / home_container_height);
    // 알고리즘이나 공식을 할 때는 실제 간단한 숫자를 대입해서 증명하는것이 중요

    home_container.style.opacity = 1-window.scrollY / (home_container_height)
})

// Show "arrow up", "dark mode" button when scrolling down
const arrow_up = document.querySelector('.arrow-up');

document.addEventListener('scroll', () =>{
    if(window.scrollY > home_container_height / 2) {
        arrow_up.classList.add('visible');
    } else {
        arrow_up.classList.remove('visible');
    }
    })

    // Handle click on the "arrow up" button
arrow_up.addEventListener('click', () => {
    scroll_into_view("#home");
})

// Handle click on the "dark-mode" button
const dark_mode = document.querySelector('.dark-mode');
const light_mode = document.querySelector('.light-mode');
const dark = 'dark';
const light = 'light';
const theme = 'theme';

function show_mode_btn (theme) {
    switch(theme) {
        case light:
        dark_mode.classList.add('visible');
        light_mode.classList.remove('visible');
        break;

        case dark:
        dark_mode.classList.remove('visible');
        light_mode.classList.add('visible');
        break;
    }
}

function get_theme() {
    const loaded_theme = localStorage.getItem(theme);
    const window_theme = window.matchMedia(`(${theme}: ${dark})`).matches ? dark : theme;    

    return loaded_theme ? loaded_theme : window_theme;
} 

window.addEventListener('load', () => {
    if (get_theme() === dark) {
        localStorage.setItem(theme, dark);

        document.documentElement.setAttribute(theme,dark);
        show_mode_btn(dark)
    } else {
        localStorage.setItem(theme, light);

        document.documentElement.setAttribute(theme, light);
        show_mode_btn(light)
    }
})

dark_mode.addEventListener('click', () => {
    document.documentElement.setAttribute(theme, dark);
    localStorage.setItem(theme, dark);
    show_mode_btn(dark);
})

light_mode.addEventListener('click', () => {
    document.documentElement.setAttribute(theme, light);
    localStorage.setItem(theme, light);
    show_mode_btn(light);
})

// Handle click on the proejct category button 
// Weekness part!!!
const work_btn_container = document.querySelector('.work__categories');
const projects_container = document.querySelector('.work__projects');
const projects = document.querySelectorAll('.project');

work_btn_container.addEventListener('click', (e) => {
    const target = e.target.nodeName === 'BUTTON' ? e.target : e.target.parentNode;
    // BUTTON 대문자로 해야 인식됨
    // nodeName 중요!
    const filter = target.dataset.filter;

    if(filter === null){
        return;
    }

    // Remove selection from the previous item and select the new one
    const active = document.querySelector('.category__btn.selected');
    active.classList.remove('selected');
    target.classList.add('selected');
    projects_container.classList.add('anim--out');

    projects.forEach((project) => {
        const type = project.dataset.type;

        if(filter === '*' || filter === type) {
            project.classList.remove('invisible');
        } else {
            project.classList.add('invisible');
        }
    }) 

    setTimeout(() => {
        projects_container.classList.remove('anim--out');
    },300)
})

function scroll_into_view(selector) {
    const scroll_to = document.querySelector(selector);

    scroll_to.scrollIntoView({behavior : 'smooth'});
    select_nav_item(nav_items[section_id.indexOf(selector)]);
}

// 매우 중요
// 1. 모든 섹션 요소들과 모든 아이템들을 가지고 온다
// 2/ intersectionObserver를 이용해서 모든 섹션들을 관찰한다
// 3. 보여지는 섹션에 해당하는 메뉴 아이템을 활성화 시킨다

const section_id = [
    '#home',
    '#about',
    '#skills',
    '#work',
    '#testimonials',
    '#contact',
];

// map API는 forEach와 다르게 배열로 다시 만들어줌
// const sections = section_id.map(function(id){
//     return document.querySelector(id);
//     return 필수!!
// })

const sections = section_id.map(id => document.querySelector(id));
const nav_items = section_id.map(id => document.querySelector(`[data-link="${id}"]`));

const observer_options = {
    root: null,
    rootMargin: '0px',
    threshold: 0.5
}

let selected_nav_index = 0;
let selected_nav_item = nav_items[0]; 

function select_nav_item(selected) {
    selected_nav_item.classList.remove('selected');
    selected_nav_item = selected;
    selected_nav_item.classList.add('selected');
}

const observer_callback = (entries, observer) => {
    entries.forEach((entry) => {
        if(!entry.isIntersecting && entry.intersectionRatio > 0) {
            const index = section_id.indexOf(`#${entry.target.id}`);
            
            if(entry.boundingClientRect.y < 0) {
                selected_nav_index = index + 1;
            } else {
                selected_nav_index = index - 1;
            }
        }
    })
}

const observer = new IntersectionObserver(observer_callback, observer_options);

sections.forEach((section) => {
    observer.observe(section);
})

window.addEventListener('wheel', () => {
    if(window.scrollY === 0) {
        selected_nav_index = 0;
    } else if (
        // window.scrollY + window.innerHeight의 값이 정확하게 일치하지 않는 경우 존재
        window.scrollY + window.innerHeight >= 
        document.body.clientHeight
        ) {
            selected_nav_index = nav_items.length - 1;
    }

    select_nav_item(nav_items[selected_nav_index]);
})

// Show skill bar animation
const skills = document.querySelector('#skills');
const skill_values = skills.querySelectorAll('.skill__value');

const skill_observer_callback = (entries, observer) => {
    entries.forEach((entry) => {
        const target = entry.target;
        
        // method 1 (use Keyframes)
        // if(entry.isIntersecting) {
        //     target.classList.add('anime');
        // } else {
        //     target.classList.remove('anime');
        //     console.log('out')
        // }
        
        // method 2 (use Dataset)
        if(entry.isIntersecting) {
            const percent = target.dataset.percent;

            target.style.width = percent;
        } else {
            // width 0으로 하면 isInterscting의 true와 false가 반복됨 (이유는 모름)
            target.style.width = '15%';
        }
    });
}

const skill_observer = new IntersectionObserver(skill_observer_callback, observer_options);

skill_values.forEach((value) => {
    skill_observer.observe(value);
})

// home icon bounce animation
const about = document.querySelector('#about');
const icons = about.querySelectorAll('.major__icon');

const icon_observer_callback = (entry, observer) => {
    if(entry[0].isIntersecting) {
        icons.forEach((icon) => {
            icon.classList.add('bounce');
        })
    } else {
        icons.forEach((icon) => {
            icon.classList.remove('bounce');
        })        
    }
};

const icon_observer = new IntersectionObserver(icon_observer_callback, observer_options);

icon_observer.observe(about);

// testimonial move animation
const testimonials = document.querySelector('#testimonials');
const testimonial = testimonials.querySelectorAll('.testimonial');

const testimonial_observer_callback = (entry, observer) => {
    if(entry[0].isIntersecting) {
        testimonial.forEach((testimonial) => {
            testimonial.classList.add('move')
        })
    } else {
        testimonial.forEach((testimonial) => {
            testimonial.classList.remove('move');
        })        
    }
};

const testimonial_observer = new IntersectionObserver(testimonial_observer_callback, observer_options);

testimonial_observer.observe(testimonials);