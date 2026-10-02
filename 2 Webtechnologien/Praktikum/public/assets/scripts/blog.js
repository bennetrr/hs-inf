/**
 * @typedef {Object} BlogPost
 * @property {string} date - The date of the blog post in "YYYY-MM-DD" format.
 * @property {number} year - The year of the blog post.
 * @property {string} month - The month of the blog post.
 * @property {number} day - The day of the month for the blog post.
 * @property {string} title - The title of the blog post.
 * @property {string[]} text - An array of paragraphs representing the blog post content.
 */

const blogFiles = [
    '/assets/blog/2023-4-17.json',
    '/assets/blog/2023-4-18.json',
    '/assets/blog/2023-4-19.json',
]

class BlogViewer extends HTMLElement {
    static observedAttributes = ['show-all-posts'];

    constructor() {
        super();
        /**@type {BlogPost[]}*/
        this.blogPosts = [];
        this.displayedBlogNumber = 0;
        this.showAllPosts = false;
    }

    async mountTemplate() {
        const response = await fetch('/assets/templates/blog.template.html');

        const wrapper = document.createElement('div');
        wrapper.innerHTML = await response.text();
        document.body.appendChild(wrapper);

        this.attachShadow({ mode: "open" });
        this.shadowRoot.appendChild(document.getElementById('blog-template').content.cloneNode(true));
    }

    async loadBlogList() {
        for (let blogFile of blogFiles) {
            const response = await fetch(blogFile);
            const blog = await response.json();
            this.blogPosts.push(blog);
        }
    }

    createBlog(index) {
        const blog = this.blogPosts[index];

        const container = this.shadowRoot.getElementById('blog');

        // Main Header
        if (!this.showAllPosts) {
            const h2 = document.createElement('h2');
            h2.appendChild(document.createTextNode('Blog'));
            h2.classList.add('first');
            container.appendChild(h2);
        }

        // Article
        const article = document.createElement('article');
        container.appendChild(article);

        // Article heading
        const heading = document.createElement('div');
        heading.classList.add('blog-heading');
        article.appendChild(heading);

        const date = document.createElement('div');
        date.classList.add('blog-date');
        heading.appendChild(date);

        const day = document.createElement('span');
        day.classList.add('blog-day');
        day.appendChild(document.createTextNode(blog.day.toString()));
        date.appendChild(day);

        const month = document.createElement('span');
        month.classList.add('blog-month');
        month.appendChild(document.createTextNode(blog.month));
        date.appendChild(month);

        const h3 = document.createElement('h3');
        h3.appendChild(document.createTextNode(blog.title));
        heading.appendChild(h3);

        // Text
        for (const paragraph of blog.text) {
            const p = document.createElement('p');
            p.appendChild(document.createTextNode(paragraph));
            article.appendChild(p);
        }

        // Controls
        if (!this.showAllPosts) {
            const controlsContainer = document.createElement('div');
            controlsContainer.classList.add('blog-controls');
            article.appendChild(controlsContainer);

            const previousButton = document.createElement('button');
            previousButton.id = 'blog-previous';
            previousButton.ariaLabel = 'Letzten Blog-Post anzeigen';
            previousButton.addEventListener('click', this.handlePreviousClick.bind(this));
            const previousIcon = document.createElement('i');
            previousIcon.classList.add('fa', 'fa-chevron-left');
            previousButton.appendChild(previousIcon);
            controlsContainer.appendChild(previousButton);

            const nextButton = document.createElement('button');
            nextButton.id = 'blog-next';
            nextButton.ariaLabel = 'Nächsten Blog-Post anzeigen';
            nextButton.addEventListener('click', this.handleNextClick.bind(this));
            const nextIcon = document.createElement('i');
            nextIcon.classList.add('fa', 'fa-chevron-right');
            nextButton.appendChild(nextIcon);
            controlsContainer.appendChild(nextButton);
        }
    }

    displayBlog() {
        this.shadowRoot.getElementById('blog').replaceChildren();

        if (this.showAllPosts) {
            this.blogPosts.forEach((_, i) => this.createBlog(i));
        } else {
            this.createBlog(this.displayedBlogNumber);
        }
    }

    handlePreviousClick() {
        if (this.displayedBlogNumber > 0) {
            this.displayedBlogNumber--;
        }

        this.displayBlog();
    }

    handleNextClick() {
        if (this.displayedBlogNumber < this.blogPosts.length - 1) {
            this.displayedBlogNumber++;
        }

        this.displayBlog();
    }

    attributeChangedCallback(name, oldValue, value) {
        if (name !== 'show-all-posts') return;
        this.showAllPosts = value;
    }

    async connectedCallback() {
        await this.mountTemplate();
        await this.loadBlogList();
        await this.displayBlog();
    }
}

customElements.define('blog-viewer', BlogViewer);
